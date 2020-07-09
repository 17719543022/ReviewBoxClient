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
    int serverPort = LocalSettings::instance()->value("Device/baseDeviceId").toInt();
    int nRet = StartHTTPServer(serverPort, &listener);
    if (nRet == 0) {
        qDebug() << "server strart port = 6666";
    } else {
        qDebug() << "server fail";
    }

    connect(&listener, &Listener::newSerialData, this, &MainWindow::on_NewSerialData);
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
    int m = INVALID_POSITION;
    int n = INVALID_POSITION;
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
