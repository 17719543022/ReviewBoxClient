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
            m = INVALID_POSITION;
            n = INVALID_POSITION;
            findLocationInTree(object.value("content").toObject().value("rfid").toString(), m, n);
            if ((m == INVALID_POSITION) && (n == INVALID_POSITION)) {
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
            m = INVALID_POSITION;
            n = INVALID_POSITION;
            findLocationInTree(object.value("content").toObject().value("rfid").toString(), m, n);

            if ((m == INVALID_POSITION) && (n == INVALID_POSITION)) {
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
                    m = INVALID_POSITION;
                    n = INVALID_POSITION;
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
