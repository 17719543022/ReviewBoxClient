#ifndef LOCALSETPAIRS_H
#define LOCALSETPAIRS_H

#include <QObject>
#include <QSettings>

class LocalSetPairs : public QSettings
{
public:
      ~LocalSetPairs();

      static LocalSetPairs* instance();

private:
      explicit LocalSetPairs(const QString &fileName, Format format, QObject *parent = nullptr);
};

inline LocalSetPairs* LocalSetPairs::instance() {
    static LocalSetPairs inst("./config/pairs.ini", QSettings::IniFormat);
    return &inst;
}

#endif // LOCALSETPAIRS_H
