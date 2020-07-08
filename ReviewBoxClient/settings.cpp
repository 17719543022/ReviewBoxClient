#include "settings.h"

LocalSettings::LocalSettings(const QString &fileName, Format format, QObject *parent)
    :QSettings(fileName, format, parent)
{

}
LocalSettings::~LocalSettings()
{

}
