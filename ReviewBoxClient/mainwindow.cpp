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
#include <QPainter>

namespace  {
int result[6];
}

void imageDataCallBack_s(long frameIndex, char *data, int len, int format, void *userData) {
    Q_UNUSED(len)
    Q_UNUSED(format)

    DataAnalysis *dataAnalysis = static_cast<DataAnalysis *>(userData);

    frameIndexs = frameIndex;
    if (frameIndexs > frameRecords) {
        emit dataAnalysis->stateCameraSChange(true);
    } else {
        emit dataAnalysis->stateCameraSChange(false);
    }

    dataAnalysis->getVideoInfo();

    QImage image(reinterpret_cast<uchar*>(data), dataAnalysis->width(), dataAnalysis->height(), QImage::Format_RGB888);

    emit dataAnalysis->newFrame_s(image);

    frameRecords = frameIndexs;
}

void imageDataCallBack_x(long frameIndex, char *data, int len, int format, void *userData) {
    Q_UNUSED(len)
    Q_UNUSED(format)

    DataAnalysis *dataAnalysis = static_cast<DataAnalysis *>(userData);

    result[0] = (result[0] + 1) % 700;
    result[1] = 30;
    result[2] = 200;
    result[3] = 200;
    if ((result[0] >= 300) && (result[0] <= 400)) {
        result[4] = 0;
    } else {
        result[4] = -1;
    }
    result[5] = 0;
    emit dataAnalysis->newResultFrame(result[0] - 200, result[1], result[2], result[3], result[4], result[5], QString());

    frameIndexc = frameIndex;
    if (frameIndexc > frameRecordc) {
        emit dataAnalysis->stateCameraXChange(true);
    } else {
        emit dataAnalysis->stateCameraXChange(false);
    }

    dataAnalysis->getVideoInfo();

    QImage image(reinterpret_cast<uchar*>(data), dataAnalysis->width(), dataAnalysis->height(), QImage::Format_RGB888);

    emit dataAnalysis->newFrame_x(image);

    frameRecordc = frameIndexc;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataAnalysis(new DataAnalysis())
    , naManager(new QNetworkAccessManager(this))
    , networkAccessTimer(new QTimer(this))
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
    for (int i = 0; i < 6; i++) {
        result[i] = 0;
    }

    connect(dataAnalysis, &DataAnalysis::newFrame_s, this, &MainWindow::display_s);
    connect(dataAnalysis, &DataAnalysis::newFrame_x, this, &MainWindow::display_x);
    connect(dataAnalysis, &DataAnalysis::stateCameraXChange, this, &MainWindow::updateStateCameraX);
    connect(dataAnalysis, &DataAnalysis::stateCameraSChange, this, &MainWindow::updateStateCameraS);
    connect(dataAnalysis, &DataAnalysis::newResultFrame, this->ui->videoLabel_x, &ReviewLabel::onNewResultFrame);
    connect(dataAnalysis, &DataAnalysis::newResultFrame, this, &MainWindow::onNewResultFrame);

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
    int serverPort = LocalSettings::instance()->value("Device/serverPort").toInt();
    int nRet = StartHTTPServer(serverPort, &listener);
    if (nRet == 0) {
        qDebug() << "server strart port: " << serverPort;
    } else {
        qDebug() << "server fail";
    }

    connect(&listener, &Listener::newSerialData, this, &MainWindow::on_NewSerialData);
    connect(&listener, &Listener::stateNetworkChange, this, &MainWindow::updateStateNetworkNormal);

    connect(naManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(baggageTrackerResponse(QNetworkReply *)));
    networkAccessTimer->setSingleShot(true);
    connect(networkAccessTimer, SIGNAL(timeout()), this, SLOT(updateStateNetworkError));
}

void MainWindow::display_x(const QImage& image) {
    QImage img = image.scaled(960
                              , 540
                              , Qt::IgnoreAspectRatio
                              , Qt::SmoothTransformation);

    this->videoImageX = image;

    ui->videoLabel_x->setPixmap(QPixmap::fromImage(img.rgbSwapped()));
}

void MainWindow::onNewResultFrame(int result0, int result1, int result2, int result3, int result4, int result5, QString boxStr) {
    Q_UNUSED(result0)
    Q_UNUSED(result1)
    Q_UNUSED(result2)
    Q_UNUSED(result3)
    Q_UNUSED(result4)

    sdkNumber = boxStr.isEmpty() ? -1 : boxStr.toInt();
    int mayBe = 0;
    bool isRfidInLifeList = false;

    if ((result[5] == -1) && (result5 == 0)) {
        if ((!boxStr.isEmpty())) {
            for (int i = 0; i < lifeList.size(); i++) {
                if ((boxStr.toInt() == lifeList.at(i).number)
                        && (lifeList.at(i).image.isNull())
                        && lifeList.at(i).isEnteredAndNotLeave) {
                    mayBe = i;
                    isRfidInLifeList = true;
                    break;
                }
            }
            if (!isRfidInLifeList) {
                for (int i = lifeList.size(); i >= 0; i--) {
                    if (lifeList.at(i).image.isNull()
                            && lifeList.at(i).isEnteredAndNotLeave) {
                        mayBe = i;
                        break;
                    }
                }
            }
        } else {
            for (int i = lifeList.size(); i >= 0; i--) {
                if (lifeList.at(i).image.isNull()
                        && lifeList.at(i).isEnteredAndNotLeave) {
                    mayBe = i;
                    break;
                }
            }
        }
    }

    lifeList.replace(mayBe, Life(lifeList.at(mayBe), videoImageX));
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

    // Header
    QString trackerUrl = LocalSettings::instance()->value("Interface/trackerUrl").toString();
    request.setUrl(QUrl(trackerUrl));
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
        // 同一个rfid第一次“2-行李框到达X光机传送带”被记录进lifeList后，如果被标记为复检，
        // 第二次“2-行李框到达X光机传送带”时，会覆盖之前的那次记录并重新维护isRecheck字段
        for (int i = 0; i < lifeList.size(); i++) {
            if (lifeList.at(i).selfRfid == object.value("content").toObject().value("rfid").toString()) {
                extraInfo.insert("isRecheck", lifeList.at(i).isRecheck);
                break;
            }
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
    networkAccessTimer->start(3000);
}

void MainWindow::updateStateCameraX(bool state)
{
    if (state) {
        ui->stateCam_x->setText("摄像头1：正常");
        ui->stateCam_x->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#00ff00;");
    } else {
        ui->stateCam_x->setText("摄像头1：故障");
        ui->stateCam_x->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#ff0000;");
    }
}

void MainWindow::updateStateCameraS(bool state)
{
    if (state) {
        ui->stateCam_s->setText("摄像头2：正常");
        ui->stateCam_s->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#00ff00;");
    } else {
        ui->stateCam_s->setText("摄像头2：故障");
        ui->stateCam_s->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#ff0000;");
    }
}

void MainWindow::updateStateNetworkError()
{
    ui->stateNet->setText("网络：故障");
    ui->stateNet->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#ff0000;");
}

void MainWindow::updateStateNetworkNormal()
{
    ui->stateNet->setText("网络：正常");
    ui->stateNet->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#00ff00;");
}

void MainWindow::baggageTrackerResponse(QNetworkReply* reply)
{
    if (reply->url() == QUrl(LocalSettings::instance()->value("Interface/trackerUrl").toString())) {
        networkAccessTimer->stop();
    }

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
    bool isNumberInLifeList = false;

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

    case 4:
        // 申皓：收到X光机传送带状态，只用在window上找个地方提示下现在传送带的状态，不做其它任何操作
        if (object.value("content").toObject().value("position").toInt() == 0) {
            ui->stateBelt->setText("传送带：停止");
            ui->stateNet->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#ff0000;");
        }
        if (object.value("content").toObject().value("position").toInt() == 1) {
            ui->stateBelt->setText("传送带：正向");
            ui->stateNet->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#00ff00;");
        }
        if (object.value("content").toObject().value("position").toInt() == 2) {
            ui->stateBelt->setText("传送带：反向");
            ui->stateNet->setStyleSheet("font-family:\"Microsoft Yahei\"; font-size:10px; background:transparent; color:#ff0000;");
        }
        break;

    case 5:
        if (sdkNumber != -1) {
            for (int i = 0; i < lifeList.size(); i++) {
                if ((lifeList.at(i).number == sdkNumber)
                        && lifeList.at(i).isEnteredAndNotLeave) {
                    lifeList.replace(i, Life(lifeList.at(i), 1));
                    isNumberInLifeList = true;
                    break;
                }
            }
            if (!isNumberInLifeList) {
                for (int i = lifeList.size() - 1; i >= 0; i--) {
                    if (lifeList.at(i).isEnteredAndNotLeave) {
                        lifeList.replace(i, Life(lifeList.at(i), 1));
                        break;
                    }
                }
            }
        } else {
            for (int i = lifeList.size() - 1; i >= 0; i--) {
                if (lifeList.at(i).isEnteredAndNotLeave) {
                    lifeList.replace(i, Life(lifeList.at(i), 1));
                    break;
                }
            }
        }
        isNumberInLifeList = false;
        if (sdkNumber != -1) {
            for (int i = 0; i < lifeList.size(); i++) {
                if ((lifeList.at(i).number == sdkNumber)
                        && lifeList.at(i).isEnteredAndNotLeave
                        && lifeList.at(i).image.isNull()) {
                    lifeList.replace(i, Life(lifeList.at(i), videoImageX));
                    isNumberInLifeList = true;
                    break;
                }
            }
            if (!isNumberInLifeList) {
                for (int i = lifeList.size() - 1; i >= 0; i--) {
                    if (lifeList.at(i).isEnteredAndNotLeave) {
                        if (lifeList.at(i).image.isNull()) {
                            lifeList.replace(i, Life(lifeList.at(i), videoImageX));
                        }
                        break;
                    }
                }
            }
        } else {
            for (int i = lifeList.size() - 1; i >= 0; i--) {
                if (lifeList.at(i).isEnteredAndNotLeave) {
                    if (lifeList.at(i).image.isNull()) {
                        lifeList.replace(i, Life(lifeList.at(i), videoImageX));
                    }
                    break;
                }
            }
        }
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
