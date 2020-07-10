#include "localsetpairs.h"

LocalSetPairs::LocalSetPairs(const QString &fileName, Format format, QObject *parent)
    : QSettings(fileName, format, parent)
{

}

LocalSetPairs::~LocalSetPairs()
{

}
