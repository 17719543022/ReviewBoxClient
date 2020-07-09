#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QJsonObject>
#include <QStringList>

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

// 存放所有的“2-行李框到达X光机传送带”消息的全局List
extern QStringList list;

// 存放所有“7-回框准备”，position为“02复查框位”消息的全局List
extern QStringList reList;

// 根rfid排在数组0位置，level为0，其它节点level为1，在tree中只要保持连续，中间没有空节点即可
extern QList<QList<RfidNode>> trees;

void findLocationInTree(QString rfid, int &m, int &n);

void addWithKnownM (int level, QString head, QString rfid, int m);

void delWithKnownRfid (QString rfid);

void dumpGlobalTree();

void dumpGlobalList();

void dumpGlobalReList();

bool parse(const QString &str, QJsonObject &object);

#endif // COMMON_H
