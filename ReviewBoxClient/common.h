#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QJsonObject>
#include <QStringList>
#include <QImage>
#include "localsetpairs.h"
#include "QDebug"

#define INVALID_LEVEL 255
#define INVALID_POSITION 65535

struct RfidNode {
    int level;
    QString head;
    QString rfid;

    RfidNode() {
        level = INVALID_LEVEL;
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

extern long frameIndexs;
extern long frameIndexc;
extern long frameRecords;
extern long frameRecordc;
extern int  sdkNumber;
extern int beltState;
extern int sdkResult[6];

struct Life {
    QString enterTime;
    QString leaveTime;
    bool isEnteredAndNotLeave;
    QString selfRfid;
    QString headRfid;
    int number;
    QImage image;
    bool isRecheck;

    Life (QString enterTime, QString selfRfid)
        : enterTime(enterTime)
        , selfRfid(selfRfid)
    {
        leaveTime = QString();
        isEnteredAndNotLeave = true;
        headRfid = QString();
        QString rfidKey = "Pairs/RFID" + selfRfid.toUpper();
        number = LocalSetPairs::instance()->value(rfidKey).toInt();
        image = QImage();
        isRecheck = false;
    }

    Life (const Life life, bool isRecheck, bool isEnteredAndNotLeave) {
        this->enterTime = life.enterTime;
        this->leaveTime = life.leaveTime;
        this->isEnteredAndNotLeave = isEnteredAndNotLeave;
        this->selfRfid = life.selfRfid;
        this->headRfid = life.headRfid;
        this->number = life.number;
        this->image = life.image;
        this->isRecheck = isRecheck;
    }

    Life (const Life life, QImage image) {
        this->enterTime = life.enterTime;
        this->leaveTime = life.leaveTime;
        this->isEnteredAndNotLeave = life.isEnteredAndNotLeave;
        this->selfRfid = life.selfRfid;
        this->headRfid = life.headRfid;
        this->number = life.number;
        this->image = image;
        this->isRecheck = life.isRecheck;
    }

    Life (const Life life, QString leaveTime) {
        this->enterTime = life.enterTime;
        this->leaveTime = leaveTime;
        this->isEnteredAndNotLeave = life.isEnteredAndNotLeave;
        this->selfRfid = life.selfRfid;
        this->headRfid = life.headRfid;
        this->number = life.number;
        this->image = life.image;
        this->isRecheck = life.isRecheck;
    }

    void dump () const {
        qDebug() << "selfRfid: " << selfRfid \
                 << "\theadRfid: " << headRfid \
                 << "\tenterTime: " << enterTime \
                 << "\tleaveTime: " << leaveTime \
                 << "\tisEnteredAndNotLeave: " << isEnteredAndNotLeave \
                 << "\tnumber: " << number \
                 << "\timage: " << (image.isNull() ? "image isNull" : "image isn't Null") \
                 << "\tisRecheck: " << isRecheck;
    }
};

// 存放所有的“2-行李框到达X光机传送带”消息的全局List
extern QList<Life> lifeList;

// 存放所有的（最多3条）“3-行李框离开X光机传送带”的记录，供MainWindow界面展示
extern QList<Life> resultList;

// 存放所有“7-回框准备”，position为“02复查框位”消息的全局List
extern QList<QString> reList;

// 根rfid排在数组0位置，level为0，其它节点level为1，在tree中只要保持连续，中间没有空节点即可
extern QList<QList<RfidNode>> trees;

void findLocationInTree(QString rfid, int &m, int &n);

void addWithKnownM (int level, QString head, QString rfid, int m);

void delWithKnownRfid (QString rfid);

void dumpGlobalTree();

void dumpGlobalLifeList();

void dumpGlobalReList();

bool parse(const QString &str, QJsonObject &object);

#endif // COMMON_H
