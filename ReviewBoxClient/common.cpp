#include "common.h"
#include <QJsonParseError>
#include "QDebug"
#include <QJsonDocument>

long frameIndexs = 0;
long frameIndexc = 0;
long frameRecords = 0;
long frameRecordc = 0;

QList<Life> lifeList = QList<Life>();

QList<QString> reList = QList<QString>();

QList<QList<RfidNode>> trees = QList<QList<RfidNode>>();

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

    m = INVALID_POSITION;
    n = INVALID_POSITION;
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
                tree << RfidNode(INVALID_LEVEL, trees.at(i).at(j).head, trees.at(i).at(j).rfid);
            } else if (trees.at(i).at(j).rfid != rfid) {
                tree << trees.at(i).at(j);
            }
        }

        if (!((tree.size() == 1) && (INVALID_LEVEL == tree.at(0).level))) {
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

void dumpGlobalLifeList() {
    qDebug() << "dumpGlobalLifeList invoked...";

    for (int i = 0; i < lifeList.size(); i++) {
        lifeList.at(i).dump();
    }
}

void dumpGlobalReList() {
    qDebug() << "dumpGlobalReList invoked...";

    for (int i = 0; i < reList.size(); i++) {
        qDebug() << "RFID: " << reList.at(i);
    }
}
