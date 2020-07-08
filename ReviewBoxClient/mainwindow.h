#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataanalysis.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "HTTPServer/HTTPServerExp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MyListen : public QObject, public RequstListener
{
    Q_OBJECT

private:
    virtual void MultipartRequstListen(const std::string& uri, const std::map<std::string, DataInfo>& mapDataInfo, std::string& strResponse);
    virtual void CommonRequstListen(const std::string& uri, const std::string& strRequestBody, std::string& strResponse);

signals:
    void newSerialData(QString strRequest);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void baggageTrackerResponse(QNetworkReply* reply);

    void display_x(const QImage& image);

    void display_s(const QImage& image);

    void on_NewSerialData(QString strRequest);

private:
    void baggageTrackerPost(int processNode, QString strRequest);

private:
    Ui::MainWindow *ui;
    DataAnalysis *dataAnalysis;
    QNetworkAccessManager *naManager;
    MyListen myListen;
    QImage shotImage;
};
#endif // MAINWINDOW_H
