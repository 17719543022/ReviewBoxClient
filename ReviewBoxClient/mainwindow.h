#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataanalysis.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "HTTPServer/HTTPServerExp.h"
#include "listener.h"
#include "common.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void baggageTrackerResponse(QNetworkReply* reply);

    void display_x(const QImage& image);

    void onNewResultFrame(int result0, int result1, int result2, int result3, int result4, int result5, QString boxStr);

    void display_s(const QImage& image);

    void on_NewSerialData(QString strRequest);

    void updateStateCameraX(bool state);

    void updateStateCameraS(bool state);

    void updateStateNetworkError();

    void updateStateNetworkNormal();

private:
    void baggageTrackerPost(int processNode, QString strRequest);

private:
    Ui::MainWindow *ui;
    DataAnalysis *dataAnalysis;
    QNetworkAccessManager *naManager;
    QTimer *networkAccessTimer;
    Listener listener;
    QImage shotImage;
    QImage videoImageX;
    int result[6];
};
#endif // MAINWINDOW_H
