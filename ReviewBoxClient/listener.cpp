#include "listener.h"
#include "QJsonObject"
#include "QDebug"
#include "QJsonDocument"
#include "common.h"

Listener::Listener()
{

}

void Listener::MultipartRequstListen(const std::string &uri, const std::map<std::string, DataInfo> &mapDataInfo, std::string &strResponse)
{
    Q_UNUSED(mapDataInfo)
    qDebug() << "uri: " << QString::fromLocal8Bit(uri.c_str());

    strResponse = "{\"reqId\":\"123\",\"status\":0,\"msg\":\"success\",\"faceNum\":1,\"faceInfo\":[{\"userInfo\":\"\",\"imgUrl\":\"\",\"score\":0.78349584,\"result\":1,\"uId\":\"\",\"fId\":\"1\"}]}";
}

void Listener::CommonRequstListen(const std::string &uri, const std::string &strRequestBody, std::string &strResponse)
{
    Q_UNUSED(uri)
    qDebug() << "strRequestBody: " << QString::fromLocal8Bit(strRequestBody.c_str());

    emit this->stateNetworkChange(true);

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
    bool isRfidInLifeList = false;

    QJsonObject json2;
    QJsonObject content2;
    QList<RfidNode> tree;
    int m = INVALID_POSITION;
    int n = INVALID_POSITION;

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

        return;
    }

    switch (object.value("content").toObject().value("type").toInt()) {
    // 2-行李框到达X光机传送带
    case 2:
        stubNumber = object.value("content").toObject().value("mode").toInt();

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

        // 1. 每一个进安检的rfid都会收到“2-行李框到达X光机传送带”
        // 2. “7-回框准备”中position为“02复查框位”时，必定附带一条“2-行李框到达X光机传送带”
        // 存lifeList的时候，一是要注意按时间存，二是如果该rfid已有记录需要更新（被覆盖）为新的
        for (int i = lifeList.size() - 1; i >= 0; i--) {
            if (lifeList.at(i).selfRfid == object.value("content").toObject().value("rfid").toString()) {
                lifeList.removeAt(i);
            }
        }

        if (lifeList.size() == 0) {
            lifeList << Life(object.value("content").toObject().value("time").toString(), object.value("content").toObject().value("rfid").toString());
        } else {
            for (int j = lifeList.size() - 1; j >= 0; j--) {
                if (object.value("content").toObject().value("time").toString() >= lifeList.at(j).enterTime) {
                    if (j == lifeList.size() - 1) {
                        lifeList << Life(object.value("content").toObject().value("time").toString(), object.value("content").toObject().value("rfid").toString());
                        break;
                    } else {
                        lifeList.insert(j + 1, Life(object.value("content").toObject().value("time").toString(), object.value("content").toObject().value("rfid").toString()));
                        break;
                    }
                }
            }
        }

        // 触发X光机前端摄像头拍照发送服务器
        emit this->newSerialData(QString::fromLocal8Bit(strRequestBody.c_str()));

        break;

    // 3-行李框离开X光机传送带
    case 3:
        for (int i = 0; i < lifeList.size(); i++) {
            if (lifeList.at(i).selfRfid == object.value("content").toObject().value("rfid").toString()) {
                lifeList.replace(i, Life(lifeList.at(i), object.value("content").toObject().value("time").toString()));
                break;
            }
        }
        json.insert("reqId", object.value("reqId").toString());
        json.insert("status", 0);
        json.insert("msg", "");
        json.insert("heartbeat", 1);
        json.insert("devicestatus", 0);

        content.insert("type", object.value("content").toObject().value("type").toInt());
        content.insert("rfid", object.value("content").toObject().value("rfid").toString());
        // 根据lifeList中存储的rfid对应的status状态，在离开X光机的时候发送给回框控制
        for (int i = 0; i < lifeList.size(); i++) {
            if (lifeList.at(i).selfRfid == object.value("content").toObject().value("rfid").toString()) {
                content.insert("status", lifeList.at(i).isRecheck);
                break;
            }
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
        beltState = object.value("content").toObject().value("status").toInt();

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
        emit this->newSerialData(QString::fromLocal8Bit(strRequestBody.c_str()));

        break;

    // 5-复查框指定
    case 5:
        json.insert("reqId", object.value("reqId").toString());
        json.insert("status", 0);
        json.insert("msg", "");
        json.insert("heartbeat", 1);
        json.insert("devicestatus", 0);

        content.insert("type", object.value("content").toObject().value("type").toInt());
        // 收到复查框指定，则必定走复检流程，须在给回框控制的回复中给出正确的根rfid。
        if (sdkNumber != -1) {
            for (int i = 0; i < lifeList.size(); i++) {
                if ((lifeList.at(i).number == sdkNumber)
                        && lifeList.at(i).isEnteredAndNotLeave) {
                    content.insert("rfid", lifeList.at(i).selfRfid);
                    isRfidInLifeList = true;
                    break;
                }
            }
            if (!isRfidInLifeList) {
                for (int i = 0; i < lifeList.size(); i++) {
                    if (lifeList.at(i).isEnteredAndNotLeave) {
                        content.insert("rfid", lifeList.at(i).selfRfid);
                        break;
                    }
                }
            }
        } else {
            for (int i = 0; i < lifeList.size(); i++) {
                if (lifeList.at(i).isEnteredAndNotLeave) {
                    content.insert("rfid", lifeList.at(i).selfRfid);
                    break;
                }
            }
        }
        content.insert("status", object.value("content").toObject().value("status").toInt());
        content.insert("position", object.value("content").toObject().value("position").toInt());
        content.insert("mode", object.value("content").toObject().value("mode").toInt());
        content.insert("time", object.value("content").toObject().value("time").toString());
        content.insert("weight", object.value("content").toObject().value("weight").toString());

        // 也需要emit消息给mainwindow（申皓确认不需要回复服务器），因为在mainwindow要更新isRecheck，还要根据实际情况看是否需要更新image
        emit this->newSerialData(QString::fromLocal8Bit(strRequestBody.c_str()));

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

        // 空框回流位和空框开包位只用维护本地lifeList、reList和trees
        if ((object.value("content").toObject().value("position").toInt() == 0)
                || (object.value("content").toObject().value("position").toInt() == 1)) {
            for (int i = lifeList.size() - 1; i >= 0; i--) {
                if (lifeList.at(i).selfRfid == object.value("content").toObject().value("rfid").toString()) {
                    lifeList.removeAt(i);
                }
            }

            m = INVALID_POSITION;
            n = INVALID_POSITION;
            findLocationInTree(object.value("content").toObject().value("rfid").toString(), m, n);
            if ((m != INVALID_POSITION) || (n != INVALID_POSITION)) {
                delWithKnownRfid(object.value("content").toObject().value("rfid").toString());
            }

            for (int j = reList.size() - 1; j >= 0; j--) {
                if (reList.at(j) == object.value("content").toObject().value("rfid").toString()) {
                    reList.removeAt(j);
                }
            }
        }

        // 复查框位需要上报服务器，前端控制所有上报服务器都是使用/api/v1/airport/baggage/tracker
        if (object.value("content").toObject().value("position").toInt() == 2) {
            // 首先将此消息存入reList中
            reList << object.value("content").toObject().value("rfid").toString();

            // 如果此rfid在trees中能找到，不管它在list中是否存在，就知道它的head了，就可以不管就是了
            m = INVALID_POSITION;
            n = INVALID_POSITION;
            findLocationInTree(object.value("content").toObject().value("rfid").toString(), m, n);

            if ((m == INVALID_POSITION) && (n == INVALID_POSITION)) {
                // 如果此rfid在trees中找不到，并且在list中存在，那么必定是tree的一个新增根节点
                isRfidInLifeList = false;
                for (int i = 0; i < lifeList.size(); i++) {
                    if (lifeList.at(i).selfRfid == object.value("content").toObject().value("rfid").toString()) {
                        isRfidInLifeList = true;
                        tree << RfidNode(0, object.value("content").toObject().value("rfid").toString(), object.value("content").toObject().value("rfid").toString());
                        trees << tree;

                        break;
                    }
                }

                // 如果此rfid未在trees中出现过，且在list中不存在，那么它要么是reList最末的object（endObject）的子，要么是reList最末的object（endObject）的兄弟，它的head就是我的head
                if (!isRfidInLifeList) {
                    m = INVALID_POSITION;
                    n = INVALID_POSITION;
                    findLocationInTree(reList.at(reList.size() - 2), m, n);
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
