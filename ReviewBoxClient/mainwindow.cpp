#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VideoDecodeImpl.h"
#include "QDebug"
#include <Qt>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUuid>
#include "settings.h"
#include <QBuffer>
#include <QJsonArray>
#include <QList>

namespace {
long frameIndexs = 0;
long frameIndexc = 0;
long frameRecords = 0;
long frameRecordc = 0;

bool parse(const QString &str, QJsonObject &object)
{
    QJsonParseError jsonParseError;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &jsonParseError);

    if (!document.isNull() && jsonParseError.error == QJsonParseError::NoError) {
        object = document.object();

        return true;
    }

    qDebug() << "QJsonParseError: " << jsonParseError.error;
    return false;
}

// 存放所有的“2-行李框到达X光机传送带”消息的全局List
QStringList list = QStringList();

// 存放所有“7-回框准备”，position为“02复查框位”消息的全局List
QStringList reList = QStringList();

struct RfidNode {
    int level;
    QString head;
    QString rfid;

    RfidNode() {
        level = 255;
        head = QString();
        rfid = QString();
    }

    RfidNode (int level, QString head, QString rfid)
        : level(level)
        , head(head)
        , rfid(rfid)
    {
    }
};

// 根rfid排在数组0位置，level为0，其它节点level为1，在tree中只要保持连续，中间没有空节点即可
QList<QList<RfidNode>> trees;

int m = 255, n = 255;

void findLocationInTree(QString rfid, int &m, int &n) {
    for (int i = 0; i < trees.size(); i++) {
        for (int j = 0; j < trees.at(i).size(); j++) {
            if (trees.at(i).at(j).rfid == rfid) {
                m = i;
                n = j;

                return;
            }
        }
    }

    m = 255;
    n = 255;
}

void addWithKnownM (int level, QString head, QString rfid, int m) {
    bool isAlreadyAdded = false;

    for (int i = 0; i < trees.size(); i++) {
        for (int j = 0; j < trees.at(i).size(); j++) {
            if (trees.at(i).at(j).rfid == rfid) {
                isAlreadyAdded = true;
            }
        }
    }

    if (!isAlreadyAdded) {
        QList<RfidNode> tree;
        for (int j = 0; j < trees.at(m).size(); j++) {
            tree << trees.at(m).at(j);
        }
        tree << RfidNode(level, head, rfid);

        trees.removeAt(m);

        trees << tree;
    }
}

void delWithKnownRfid (QString rfid)
{
    QList<QList<RfidNode>> laterTrees;

    for (int i = 0; i < trees.size(); i++) {
        QList<RfidNode> tree;
        for (int j = 0; j < trees.at(i).size(); j++) {
            if ((j == 0) && (trees.at(i).at(j).rfid == rfid)) {
                tree << RfidNode(255, trees.at(i).at(j).head, trees.at(i).at(j).rfid);
            } else if (trees.at(i).at(j).rfid != rfid) {
                tree << trees.at(i).at(j);
            }
        }

        if (!((tree.size() == 1) && (255 == tree.at(0).level))) {
            laterTrees << tree;
        }
    }

    trees = laterTrees;
}

void dumpGlobalTree() {
    qDebug() << "dumpGlobalTree invoked...";

    for (int i = 0; i < trees.size(); i++) {
        qDebug() << "//////////////////////////";
        qDebug() << "         rfid: " << trees.at(i).at(0).rfid;
        qDebug() << "//////////////////////////";
        for (int j = 0; j < trees.at(i).size(); j++) {
            qDebug() << "level: " << trees.at(i).at(j).level << " head: " << trees.at(i).at(j).head << " rfid: " << trees.at(i).at(j).rfid;
        }
    }
}

void dumpGlobalList() {
    qDebug() << "dumpGlobalList invoked...";

    for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); constIterator++) {
        qDebug() << *constIterator;
    }
}

void dumpGlobalReList() {
    qDebug() << "dumpGlobalReList invoked...";

    for (QStringList::const_iterator constIterator = reList.constBegin(); constIterator != reList.constEnd(); constIterator++) {
        qDebug() << *constIterator;
    }
}
}

void MyListen::MultipartRequstListen(const std::string &uri, const std::map<std::string, DataInfo> &mapDataInfo, std::string &strResponse)
{
    Q_UNUSED(mapDataInfo)
    qDebug() << "uri: " << QString::fromLocal8Bit(uri.c_str());

    strResponse = "{\"reqId\":\"123\",\"status\":0,\"msg\":\"success\",\"faceNum\":1,\"faceInfo\":[{\"userInfo\":\"\",\"imgUrl\":\"\",\"score\":0.78349584,\"result\":1,\"uId\":\"\",\"fId\":\"1\"}]}";
}

void MyListen::CommonRequstListen(const std::string &uri, const std::string &strRequestBody, std::string &strResponse)
{
    Q_UNUSED(uri)
    qDebug() << "strRequestBody: " << QString::fromLocal8Bit(strRequestBody.c_str());

    QJsonObject object;
    if (!parse(QString::fromLocal8Bit(strRequestBody.c_str()), object)) {
        return;
    }

    QJsonObject json;
    QJsonObject content;
    QStringList::const_iterator constIterator;
    QJsonObject itObject = QJsonObject();
    QJsonObject endObject = QJsonObject(); // reList中最末QString转换得到的object
    QStringList laterList = QStringList();
    bool isOnceOkAtLeaveXRay = false;
    bool isRfidInList = false;

    QJsonObject json2;
    QJsonObject content2;
    QList<RfidNode> tree;

    if (object.value("heartbeat").toInt() == 0) {
        json.insert("reqId", object.value("reqId").toString());
        json.insert("status", 0);
        json.insert("msg", "");
        json.insert("heartbeat", 0);
        if ((frameIndexc > frameRecordc) && (frameIndexs > frameRecords)) {
            json.insert("devicestatus", 0);
        } else {
            json.insert("devicestatus", 1);
        }

        content.insert("type", object.value("content").toObject().value("type").toInt());
        content.insert("rfid", object.value("content").toObject().value("rfid").toString());
        content.insert("status", object.value("content").toObject().value("status").toInt());
        content.insert("position", object.value("content").toObject().value("position").toInt());
        content.insert("mode", object.value("content").toObject().value("mode").toInt());
        content.insert("time", object.value("content").toObject().value("time").toString());
        content.insert("weight", object.value("content").toObject().value("weight").toString());

        json.insert("content", content);
        strResponse = QString(QJsonDocument(json).toJson()).toStdString();
        qDebug() << "strResponse: " << QString::fromLocal8Bit(strResponse.c_str());

        frameRecordc = frameIndexc;
        frameRecords = frameIndexs;

        return;
    }

    switch (object.value("content").toObject().value("type").toInt()) {
    // 2-行李框到达X光机传送带
    case 2:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("status", 0);
        json.insert("msg", "");
        json.insert("heartbeat", 1);
        json.insert("devicestatus", 0);

        content.insert("type", object.value("content").toObject().value("type").toInt());
        content.insert("rfid", object.value("content").toObject().value("rfid").toString());
        content.insert("status", object.value("content").toObject().value("status").toInt());
        content.insert("position", object.value("content").toObject().value("position").toInt());
        content.insert("mode", object.value("content").toObject().value("mode").toInt());
        content.insert("time", object.value("content").toObject().value("time").toString());
        content.insert("weight", object.value("content").toObject().value("weight").toString());

        // 1. 同一个rfid第一次“2-行李框到达X光机传送带”的时候
        // 2. “7-回框准备”中position为“02复查框位”时，必定附带一条“2-行李框到达X光机传送带”的时候
        // 都存下来，并且都将status存为0
        json2.insert("reqId", object.value("reqId").toString());
        json2.insert("heartbeat", object.value("heartbeat").toInt());

        content2.insert("type", object.value("content").toObject().value("type").toInt());
        content2.insert("rfid", object.value("content").toObject().value("rfid").toString());
        content2.insert("status", 0);
        content2.insert("position", object.value("content").toObject().value("position").toInt());
        content2.insert("mode", object.value("content").toObject().value("mode").toInt());
        content2.insert("time", object.value("content").toObject().value("time").toString());
        content2.insert("weight", object.value("content").toObject().value("weight").toString());

        json2.insert("content", content2);
        list << QString(QJsonDocument(json2).toJson());

        // 触发X光机前端摄像头拍照发送服务器
        emit this->newSerialData(QString::fromLocal8Bit(strRequestBody.c_str()));

        break;

    // 3-行李框离开X光机传送带
    case 3:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("status", 0);
        json.insert("msg", "");
        json.insert("heartbeat", 1);
        json.insert("devicestatus", 0);

        content.insert("type", object.value("content").toObject().value("type").toInt());
        content.insert("rfid", object.value("content").toObject().value("rfid").toString());
        // 应对同一个rfid第一次标记为复检，第二次没有标记的场景，只要list中找到一次status为0即回复0
        isOnceOkAtLeaveXRay = false;
        for (constIterator = list.begin(); constIterator != list.end(); constIterator++) {
            parse(*constIterator, itObject);
            if ((itObject.value("content").toObject().value("rfid").toString() == object.value("content").toObject().value("rfid").toString())
                    && (itObject.value("content").toObject().value("status").toInt() == 0)){
                isOnceOkAtLeaveXRay = true;
                break;
            }
        }
        if (isOnceOkAtLeaveXRay) {
            content.insert("status", 0);
        } else {
            content.insert("status", 1);
        }
        content.insert("position", object.value("content").toObject().value("position").toInt());
        content.insert("mode", object.value("content").toObject().value("mode").toInt());
        content.insert("time", object.value("content").toObject().value("time").toString());
        content.insert("weight", object.value("content").toObject().value("weight").toString());

        // 出X光机的回框控制侧的请求不用放入list中
        // 出X光机后（带复查框指定结果+图片）
        emit this->newSerialData(QString::fromLocal8Bit(strRequestBody.c_str()));

        break;

    // 4-X光机传送带状态
    case 4:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("status", 0);
        json.insert("msg", "");
        json.insert("heartbeat", 1);
        json.insert("devicestatus", 0);

        content.insert("type", object.value("content").toObject().value("type").toInt());
        content.insert("rfid", object.value("content").toObject().value("rfid").toString());
        content.insert("status", object.value("content").toObject().value("status").toInt());
        content.insert("position", object.value("content").toObject().value("position").toInt());
        content.insert("mode", object.value("content").toObject().value("mode").toInt());
        content.insert("time", object.value("content").toObject().value("time").toString());
        content.insert("weight", object.value("content").toObject().value("weight").toString());

        // 申皓：收到X光机传送带状态，只用在window上找个地方提示下现在传送带的状态，不做其它任何操作

        break;

    // 5-复查框指定
    case 5:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("status", 0);
        json.insert("msg", "");
        json.insert("heartbeat", 1);
        json.insert("devicestatus", 0);

        content.insert("type", object.value("content").toObject().value("type").toInt());
        // rfid根据SDK判别结果得到，为了测试，这里假设根据输入获取rfid
        content.insert("rfid", object.value("content").toObject().value("rfid").toString()); // TODO
        content.insert("status", object.value("content").toObject().value("status").toInt());
        content.insert("position", object.value("content").toObject().value("position").toInt());
        content.insert("mode", object.value("content").toObject().value("mode").toInt());
        content.insert("time", object.value("content").toObject().value("time").toString());
        content.insert("weight", object.value("content").toObject().value("weight").toString());

        // 收到复查框指定，则必定走复检流程，须在给回框控制的回复中给出正确的rfid。等到离开x光机的时候，回复type（3）的时候，status按“可疑状态（00：正常，01：需复查）”回复
        // 申皓确认工作人员按这一下，不用给服务器回消息
        for (constIterator = list.constBegin(); constIterator != list.constEnd(); constIterator++) {
            parse(*constIterator, itObject);
            if (object.value("content").toObject().value("rfid").toString() == itObject.value("content").toObject().value("rfid").toString()) {
                QJsonObject json;
                json.insert("reqId", itObject.value("reqId").toString());
                json.insert("heartbeat", itObject.value("heartbeat").toInt());

                QJsonObject content = QJsonObject();
                content.insert("type", itObject.value("content").toObject().value("type").toInt());
                content.insert("rfid", itObject.value("content").toObject().value("rfid").toString());
                content.insert("status", 1);
                content.insert("position", itObject.value("content").toObject().value("position").toInt());
                content.insert("mode", itObject.value("content").toObject().value("mode").toInt());
                content.insert("time", itObject.value("content").toObject().value("time").toString());
                content.insert("weight", itObject.value("content").toObject().value("weight").toString());

                json.insert("content", content);
                laterList << QString(QJsonDocument(json).toJson());
            } else {
                laterList << *constIterator;
            }
        }
        list = laterList;

        break;

    // 7-回框准备
    case 7:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("status", 0);
        json.insert("msg", "");
        json.insert("heartbeat", 1);
        json.insert("devicestatus", 0);

        content.insert("type", object.value("content").toObject().value("type").toInt());
        content.insert("rfid", object.value("content").toObject().value("rfid").toString());
        content.insert("status", object.value("content").toObject().value("status").toInt());
        content.insert("position", object.value("content").toObject().value("position").toInt());
        content.insert("mode", object.value("content").toObject().value("mode").toInt());
        content.insert("time", object.value("content").toObject().value("time").toString());
        content.insert("weight", object.value("content").toObject().value("weight").toString());

        // 空框回流位和空框开包位只用维护本地list、reList和trees
        if ((object.value("content").toObject().value("position").toInt() == 0)
                || (object.value("content").toObject().value("position").toInt() == 1)) {
            m = 255;
            n = 255;
            findLocationInTree(object.value("content").toObject().value("rfid").toString(), m, n);
            if ((m == 255) && (n == 255)) {
                for (constIterator = list.constBegin(); constIterator != list.constEnd(); constIterator++) {
                    parse(*constIterator, itObject);
                    if (object.value("content").toObject().value("rfid").toString() != itObject.value("content").toObject().value("rfid").toString()) {
                        laterList << *constIterator;
                    }
                }

                list = laterList;
            } else {
                for (constIterator = list.constBegin(); constIterator != list.constEnd(); constIterator++) {
                    parse(*constIterator, itObject);
                    if (itObject.value("content").toObject().value("rfid").toString() != object.value("content").toObject().value("rfid").toString()) {
                        laterList << *constIterator;
                    }
                }

                list = laterList;
                delWithKnownRfid(object.value("content").toObject().value("rfid").toString());
            }

            laterList = QStringList();
            for (constIterator = reList.constBegin(); constIterator != reList.constEnd(); constIterator++) {
                parse(*constIterator, itObject);
                if (itObject.value("content").toObject().value("rfid").toString() != object.value("content").toObject().value("rfid").toString()) {
                    laterList << *constIterator;
                }
            }
            reList = laterList;
        }
        // 复查框位需要上报服务器，前端控制所有上报服务器都是使用/api/v1/airport/baggage/tracker
        if (object.value("content").toObject().value("position").toInt() == 2) {
            // 首先将此消息存入reList中
            reList << QString::fromLocal8Bit(strRequestBody.c_str());

            // 如果此rfid在trees中能找到，不管它在list中是否存在，就知道它的head了，就可以不管就是了
            m = 255;
            n = 255;
            findLocationInTree(object.value("content").toObject().value("rfid").toString(), m, n);

            if ((m == 255) && (n == 255)) {
                // 如果此rfid在trees中找不到，并且在list中存在，那么必定是tree的一个新增根节点
                isRfidInList = false;
                for (constIterator = list.constBegin(); constIterator != list.constEnd(); constIterator++) {
                    parse(*constIterator, itObject);
                    if ((itObject.value("content").toObject().value("rfid").toString() == object.value("content").toObject().value("rfid").toString())) {
                        isRfidInList = true;
                        tree << RfidNode(0, object.value("content").toObject().value("rfid").toString(), object.value("content").toObject().value("rfid").toString());
                        trees << tree;

                        break;
                    }
                }

                // 如果此rfid未在trees中出现过，且在list中不存在，那么它要么是reList最末的object（endObject）的子，要么是reList最末的object（endObject）的兄弟，它的head就是我的head
                if (!isRfidInList) {
                    constIterator = reList.constEnd() - 2;
                    parse(*constIterator, endObject);
                    m = 255;
                    n = 255;
                    findLocationInTree(endObject.value("content").toObject().value("rfid").toString(), m, n);
                    addWithKnownM(1, trees.at(m).at(0).head, object.value("content").toObject().value("rfid").toString(), m);
                }
            }
        }

        emit this->newSerialData(QString::fromLocal8Bit(strRequestBody.c_str()));
        break;

    default:
        qDebug() << "not expected type: " << object.value("content").toObject().value("type").toInt();
        break;
    }

    if (json.isEmpty() || content.isEmpty()) {
        strResponse = "not expected type";
    } else {
        json.insert("content", content);
        strResponse = QString(QJsonDocument(json).toJson()).toStdString();
        qDebug() << "strResponse: " << QString::fromLocal8Bit(strResponse.c_str());
    }
}

void imageDataCallBack_s(long frameIndex, char *data, int len, int format, void *userData) {
    Q_UNUSED(len)
    Q_UNUSED(format)

    frameIndexs = frameIndex;

    DataAnalysis *dataAnalysis = static_cast<DataAnalysis *>(userData);

    dataAnalysis->getVideoInfo();

    QImage image(reinterpret_cast<uchar*>(data), dataAnalysis->width(), dataAnalysis->height(), QImage::Format_RGB888);

    emit dataAnalysis->newFrame_s(image);
}

void imageDataCallBack_x(long frameIndex, char *data, int len, int format, void *userData) {
    Q_UNUSED(len)
    Q_UNUSED(format)

    frameIndexc = frameIndex;

    DataAnalysis *dataAnalysis = static_cast<DataAnalysis *>(userData);

    dataAnalysis->getVideoInfo();

    QImage image(reinterpret_cast<uchar*>(data), dataAnalysis->width(), dataAnalysis->height(), QImage::Format_RGB888);

    emit dataAnalysis->newFrame_x(image);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataAnalysis(new DataAnalysis())
    , naManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    connect(dataAnalysis, &DataAnalysis::newFrame_s, this, &MainWindow::display_s);

    connect(dataAnalysis, &DataAnalysis::newFrame_x, this, &MainWindow::display_x);

    qDebug() << "version: " << videoDecodeGetVersion();

    int res_s = 0, res_x = 0, videoId_s = 0, videoId_x = 0;

//    打开前置顶朝下的USB摄像头
    const char param_s[] = "USB-Camera,0,640,480,15";

    res_s = videoDecodeStart2("usb", param_s, 0, VideoDecodeType_NOSHOW, imageDataCallBack_s, static_cast<void *>(dataAnalysis), &videoId_s);

    qDebug() << "videoId_s: " << videoId_s;

    if (res_s != 0) {
        qDebug() << "videoDecodeStart2 invokes failed: " << res_s;
    } else {
        dataAnalysis->updateVideoId(videoId_s);
    }

//    打开X光机分屏过来的视频
//    const char param[] = "172.18.2.213,8000,admin,cigit2019";
    const char param_x[] = "USB-Camera,1,640,480,15";

    res_x = videoDecodeStart2("usb", param_x, 0, VideoDecodeType_NOSHOW, imageDataCallBack_x, static_cast<void *>(dataAnalysis), &videoId_x);

    qDebug() << "videoId_x: " << videoId_x;

    if (res_x != 0) {
        qDebug() << "videoDecodeStart2 invokes failed: " << res_x;
    } else {
        dataAnalysis->updateVideoId(videoId_x);
    }

//    开启HTTP服务StartHTTPServer
    int nRet = StartHTTPServer(6666, &myListen);
    if (nRet == 0) {
        qDebug() << "server strart port = 6666";
    } else {
        qDebug() << "server fail";
    }

    connect(&myListen, &MyListen::newSerialData, this, &MainWindow::on_NewSerialData);
}

void MainWindow::display_x(const QImage& image) {
    QImage img = image.scaled(960
                              , 540
                              , Qt::IgnoreAspectRatio
                              , Qt::SmoothTransformation);

    ui->videoLabel_x->setPixmap(QPixmap::fromImage(img.rgbSwapped()));
}

void MainWindow::display_s(const QImage &image) {
    QImage img = image.scaled(960
                              , 540
                              , Qt::IgnoreAspectRatio
                              , Qt::SmoothTransformation);

    this->shotImage = image;

    ui->videoLabel_s->setPixmap(QPixmap::fromImage(img.rgbSwapped()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::baggageTrackerPost(int processNode, QString strRequest)
{
    QNetworkRequest request;

    connect(naManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(baggageTrackerResponse(QNetworkReply *)));

    // Header
    QString luggageUrl = "http://192.168.1.27:10080/api/v1/airport/baggage/tracker";
    request.setUrl(QUrl(luggageUrl));
    QString contentType = "application/json";
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);
    QString apiId = "123456";
    request.setRawHeader("apiId", apiId.toLatin1());
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    request.setRawHeader("timestamp", timestamp.toLatin1());
    QString apiKey = "1285384ddfb057814bad78127bc789be";
    QString temp = "/api/v1/airport/baggage/tracker" + timestamp + apiKey;
    QByteArray bb = QCryptographicHash::hash(temp.toLatin1(), QCryptographicHash::Md5);
    QString sign = QString().append(bb.toHex());
    request.setRawHeader("sign", sign.toLatin1());

    QJsonObject object;
    if (!parse(strRequest, object)) {
        return;
    }

    // Body
    QJsonObject json;
    QJsonObject extraInfo;
    bool isOnceOkAtLeaveXRay = false;
    QJsonObject item;
    QJsonObject itObject;
    QJsonArray imgs = QJsonArray();
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    shotImage.save(&buffer, "png");
    QJsonDocument doc;
    switch (processNode) {
    case 1:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("rfid", object.value("content").toObject().value("rfid").toString());
        json.insert("baseDeviceId", LocalSettings::instance()->value("Device/baseDeviceId").toString());
        json.insert("channelCode", LocalSettings::instance()->value("Device/channelCode").toString());
        json.insert("processNode", processNode);
        extraInfo.insert("isRecheck", 0);
        extraInfo.insert("checkResult", 0);
        extraInfo.insert("rfId", QString());
        json.insert("extraInfo", extraInfo);
        item.insert("photoName", "processNodeis1");
        item.insert("imgData", byteArray.toBase64().data());
        imgs.append(item);
        json.insert("imgs", imgs);
        break;

    case 2:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("rfid", object.value("content").toObject().value("rfid").toString());
        json.insert("baseDeviceId", LocalSettings::instance()->value("Device/baseDeviceId").toString());
        json.insert("channelCode", LocalSettings::instance()->value("Device/channelCode").toString());
        json.insert("processNode", processNode);
        // 应对同一个rfid第一次标记为复检，第二次没有标记的场景，只要list中找到一次status为0即回复0
        for (QStringList::const_iterator constIterator = list.begin(); constIterator != list.end(); constIterator++) {
            parse(*constIterator, itObject);
            if ((itObject.value("content").toObject().value("rfid").toString() == object.value("content").toObject().value("rfid").toString())
                    && (itObject.value("content").toObject().value("status").toInt() == 0)){
                isOnceOkAtLeaveXRay = true;
                break;
            }
        }
        if (isOnceOkAtLeaveXRay) {
            extraInfo.insert("isRecheck", 0);
        } else {
            extraInfo.insert("isRecheck", 1);
        }
        extraInfo.insert("checkResult", 0);
        extraInfo.insert("rfId", QString());
        json.insert("extraInfo", extraInfo);
        item.insert("photoName", "processNodeis2");
        item.insert("imgData", byteArray.toBase64().data());
        imgs.append(item);
        json.insert("imgs", imgs);
        break;

    // 5-回框准备中复查框位
    case 5:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("rfid", object.value("content").toObject().value("rfid").toString());
        json.insert("baseDeviceId", LocalSettings::instance()->value("Device/baseDeviceId").toString());
        json.insert("channelCode", LocalSettings::instance()->value("Device/channelCode").toString());
        json.insert("processNode", processNode);
        extraInfo.insert("isRecheck", 0);
        extraInfo.insert("checkResult", 0);
        findLocationInTree(object.value("content").toObject().value("rfid").toString(), m, n);
        extraInfo.insert("rfid", trees.at(m).at(0).rfid);
        json.insert("extraInfo", extraInfo);
        item.insert("photoName", "processNodeis2");
        item.insert("imgData", byteArray.toBase64().data());
        imgs.append(item);
        json.insert("imgs", imgs);
        break;

    // 6-回框准备中空框回流位
    case 6:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("rfid", object.value("content").toObject().value("rfid").toString());
        json.insert("baseDeviceId", LocalSettings::instance()->value("Device/baseDeviceId").toString());
        json.insert("channelCode", LocalSettings::instance()->value("Device/channelCode").toString());
        json.insert("processNode", processNode);
        extraInfo.insert("isRecheck", 0);
        extraInfo.insert("checkResult", 0);
        extraInfo.insert("rfid", QString());
        json.insert("extraInfo", extraInfo);
        item.insert("photoName", "processNodeis2");
        item.insert("imgData", byteArray.toBase64().data());
        imgs.append(item);
        json.insert("imgs", imgs);
        break;

    // 7-回框准备中空框开包位
    case 7:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("rfid", object.value("content").toObject().value("rfid").toString());
        json.insert("baseDeviceId", LocalSettings::instance()->value("Device/baseDeviceId").toString());
        json.insert("channelCode", LocalSettings::instance()->value("Device/channelCode").toString());
        json.insert("processNode", processNode);
        extraInfo.insert("isRecheck", 0);
        extraInfo.insert("checkResult", 0);
        extraInfo.insert("rfid", QString());
        json.insert("extraInfo", extraInfo);
        item.insert("photoName", "processNodeis2");
        item.insert("imgData", byteArray.toBase64().data());
        imgs.append(item);
        json.insert("imgs", imgs);
        break;

    default:
        break;
    }

    qDebug() << "MainWindow::baggageTrackerPost invoked, processNode: " << json.value("processNode").toInt();
    qDebug() << "MainWindow::baggageTrackerPost invoked, isRecheck: " << json.value("extraInfo").toObject().value("isRecheck").toInt();
    qDebug() << "MainWindow::baggageTrackerPost invoked, rfid: " << json.value("extraInfo").toObject().value("rfid").toString();

    doc.setObject(json);
    QByteArray array = doc.toJson(QJsonDocument::Compact);

    naManager->post(request, array);
}

void MainWindow::baggageTrackerResponse(QNetworkReply* reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (statusCode.isValid()) {
        qDebug() << "status code: " << statusCode.toInt();
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);

    if (reason.isValid()) {
        qDebug() << "reason: " << reason;
    }

    QNetworkReply::NetworkError err = reply->error();

    if (err != QNetworkReply::NoError) {
        qDebug() << "err: " << reply->errorString();
    } else {
        QByteArray all = reply->readAll();

        QJsonParseError err;
        QJsonDocument document = QJsonDocument::fromJson(all, &err);

        if (err.error == QJsonParseError::NoError) {
            qDebug() << "document: " << document;
        } else {
            qDebug() << "error: " << err.error;
        }
    }
}

void MainWindow::on_NewSerialData(QString strRequest)
{
    QJsonObject object = QJsonObject();
    if (!parse(strRequest, object)) {
        return;
    }

    int type = object.value("content").toObject().value("type").toInt();
    switch (type) {
    case 2:
        ui->portraitLabel_s->setPixmap(QPixmap::fromImage(shotImage.rgbSwapped()));
        // 1-进X光机前（带图片）
        baggageTrackerPost(1, strRequest);
        break;

    case 3:
        // 2-出X光机后（带复查框指定结果+图片）
        baggageTrackerPost(2, strRequest);
        break;

    case 7:
        // 5-回框准备中复查框位，
        // 6-回框准备中空框回流位，
        // 7-回框准备中空框开包位
        if (object.value("content").toObject().value("position").toInt() == 0) {
            baggageTrackerPost(6, strRequest);
        }
        if (object.value("content").toObject().value("position").toInt() == 1) {
            baggageTrackerPost(7, strRequest);
        }
        if (object.value("content").toObject().value("position").toInt() == 2) {
            baggageTrackerPost(5, strRequest);
        }
        break;

    default:
        break;
    }
}
