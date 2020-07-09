#ifndef MYLISTENER_H
#define MYLISTENER_H

#include <QObject>
#include "HTTPServer/HTTPServerExp.h"

class Listener : public QObject, public RequstListener
{
    Q_OBJECT

public:
    Listener();

private:
    virtual void MultipartRequstListen(const std::string& uri, const std::map<std::string, DataInfo>& mapDataInfo, std::string& strResponse);
    virtual void CommonRequstListen(const std::string& uri, const std::string& strRequestBody, std::string& strResponse);

signals:
    void newSerialData(QString strRequest);
};


#endif // MYLISTENER_H
