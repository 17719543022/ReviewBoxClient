/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <reviewlabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *meiTouLabel;
    QWidget *resultWidget;
    QLabel *titleLabel;
    QLabel *solidSplitLabel;
    QLabel *dashSplitLabel_1;
    QLabel *dashSplitLabel_2;
    QWidget *listWidget_1;
    QLabel *portraitLabel_1;
    QLabel *rfidTitleLabel_1;
    QLabel *rfidValueLabel_1;
    QLabel *posTitleLabel_1;
    QLabel *posValueLabel_1;
    QLabel *timeTitlelabel_1;
    QLabel *timeValueLabel_1;
    QLabel *resultTitlelabel_1;
    QLabel *resultValuelabel_1;
    QLabel *noTitleLabel_1;
    QLabel *noValueLabel_1;
    QWidget *listWidget_2;
    QLabel *portraitLabel_2;
    QLabel *rfidTitleLabel_2;
    QLabel *rfidValueLabel_2;
    QLabel *posTitleLabel_2;
    QLabel *posValueLabel_2;
    QLabel *timeTitlelabel_2;
    QLabel *timeValueLabel_2;
    QLabel *resultTitlelabel_2;
    QLabel *resultValuelabel_2;
    QLabel *noTitleLabel_2;
    QLabel *noValueLabel_2;
    QWidget *listWidget_3;
    QLabel *portraitLabel_3;
    QLabel *rfidTitleLabel_3;
    QLabel *rfidValueLabel_3;
    QLabel *posTitleLabel_3;
    QLabel *posValueLabel_3;
    QLabel *timeTitlelabel_3;
    QLabel *timeValueLabel_3;
    QLabel *resultTitlelabel_3;
    QLabel *resultValuelabel_3;
    QLabel *noValueLabel_3;
    QLabel *noTitleLabel_3;
    QLabel *dashSplitLabel_3;
    QWidget *videoWidget;
    ReviewLabel *videoLabel_x;
    QLabel *videoLabel_s;
    QLabel *portraitLabel_s;
    QWidget *rfidWidget;
    QLabel *rfidLabel_1;
    QLabel *rfidLabel_2;
    QLabel *stateNet;
    QLabel *stateCam_x;
    QLabel *stateCam_s;
    QLabel *stateBelt;
    QLabel *stateCam_x_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/BG-\346\213\267\350\264\235-2.png);"));
        meiTouLabel = new QLabel(centralwidget);
        meiTouLabel->setObjectName(QString::fromUtf8("meiTouLabel"));
        meiTouLabel->setGeometry(QRect(0, 0, 800, 45));
        meiTouLabel->setStyleSheet(QString::fromUtf8("background: 0;\n"
"image: url(:/Images/\347\234\211\345\244\264-\346\213\267\350\264\235-\346\226\260.png);"));
        resultWidget = new QWidget(centralwidget);
        resultWidget->setObjectName(QString::fromUtf8("resultWidget"));
        resultWidget->setGeometry(QRect(510, 55, 282, 535));
        resultWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/\345\217\263.png);"));
        titleLabel = new QLabel(resultWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(0, 5, 282, 30));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(false);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("image: 0;\n"
"background: 0;\n"
"color: rgb(0, 228, 255);"));
        titleLabel->setAlignment(Qt::AlignCenter);
        solidSplitLabel = new QLabel(resultWidget);
        solidSplitLabel->setObjectName(QString::fromUtf8("solidSplitLabel"));
        solidSplitLabel->setGeometry(QRect(12, 38, 258, 2));
        solidSplitLabel->setStyleSheet(QString::fromUtf8("image: 0;\n"
"background: 0;\n"
"border-width: 3px;\n"
"border-style: solid;\n"
"border-color: rgb(0, 198, 255);"));
        dashSplitLabel_1 = new QLabel(resultWidget);
        dashSplitLabel_1->setObjectName(QString::fromUtf8("dashSplitLabel_1"));
        dashSplitLabel_1->setGeometry(QRect(12, 168, 258, 2));
        dashSplitLabel_1->setStyleSheet(QString::fromUtf8("image: 0;\n"
"background: 0;\n"
"border-width: 1px;\n"
"border-style: dashed;\n"
"border-color: rgb(0, 198, 255);"));
        dashSplitLabel_2 = new QLabel(resultWidget);
        dashSplitLabel_2->setObjectName(QString::fromUtf8("dashSplitLabel_2"));
        dashSplitLabel_2->setGeometry(QRect(12, 296, 258, 2));
        dashSplitLabel_2->setStyleSheet(QString::fromUtf8("image: 0;\n"
"background: 0;\n"
"border-width: 1px;\n"
"border-style: dashed;\n"
"border-color: rgb(0, 198, 255);"));
        listWidget_1 = new QWidget(resultWidget);
        listWidget_1->setObjectName(QString::fromUtf8("listWidget_1"));
        listWidget_1->setGeometry(QRect(0, 50, 282, 108));
        listWidget_1->setStyleSheet(QString::fromUtf8("image: 0;\n"
"background: 0;"));
        portraitLabel_1 = new QLabel(listWidget_1);
        portraitLabel_1->setObjectName(QString::fromUtf8("portraitLabel_1"));
        portraitLabel_1->setGeometry(QRect(12, 0, 144, 108));
        portraitLabel_1->setStyleSheet(QString::fromUtf8("background-color: rgb(158, 158, 158);\n"
"image: url(:/Images/\345\233\276\345\203\217_images19.png);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-color: rgb(0, 228, 255);"));
        rfidTitleLabel_1 = new QLabel(listWidget_1);
        rfidTitleLabel_1->setObjectName(QString::fromUtf8("rfidTitleLabel_1"));
        rfidTitleLabel_1->setGeometry(QRect(164, 0, 40, 17));
        QFont font1;
        font1.setPointSize(10);
        rfidTitleLabel_1->setFont(font1);
        rfidTitleLabel_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        rfidValueLabel_1 = new QLabel(listWidget_1);
        rfidValueLabel_1->setObjectName(QString::fromUtf8("rfidValueLabel_1"));
        rfidValueLabel_1->setGeometry(QRect(210, 0, 60, 17));
        rfidValueLabel_1->setFont(font1);
        rfidValueLabel_1->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        posTitleLabel_1 = new QLabel(listWidget_1);
        posTitleLabel_1->setObjectName(QString::fromUtf8("posTitleLabel_1"));
        posTitleLabel_1->setGeometry(QRect(164, 44, 40, 17));
        posTitleLabel_1->setFont(font1);
        posTitleLabel_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        posValueLabel_1 = new QLabel(listWidget_1);
        posValueLabel_1->setObjectName(QString::fromUtf8("posValueLabel_1"));
        posValueLabel_1->setGeometry(QRect(210, 44, 60, 17));
        posValueLabel_1->setFont(font1);
        posValueLabel_1->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        timeTitlelabel_1 = new QLabel(listWidget_1);
        timeTitlelabel_1->setObjectName(QString::fromUtf8("timeTitlelabel_1"));
        timeTitlelabel_1->setGeometry(QRect(164, 66, 40, 17));
        timeTitlelabel_1->setFont(font1);
        timeTitlelabel_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        timeValueLabel_1 = new QLabel(listWidget_1);
        timeValueLabel_1->setObjectName(QString::fromUtf8("timeValueLabel_1"));
        timeValueLabel_1->setGeometry(QRect(210, 66, 60, 17));
        timeValueLabel_1->setFont(font1);
        timeValueLabel_1->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        resultTitlelabel_1 = new QLabel(listWidget_1);
        resultTitlelabel_1->setObjectName(QString::fromUtf8("resultTitlelabel_1"));
        resultTitlelabel_1->setGeometry(QRect(164, 88, 40, 17));
        resultTitlelabel_1->setFont(font1);
        resultTitlelabel_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        resultValuelabel_1 = new QLabel(listWidget_1);
        resultValuelabel_1->setObjectName(QString::fromUtf8("resultValuelabel_1"));
        resultValuelabel_1->setGeometry(QRect(210, 88, 60, 17));
        resultValuelabel_1->setFont(font1);
        resultValuelabel_1->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        noTitleLabel_1 = new QLabel(listWidget_1);
        noTitleLabel_1->setObjectName(QString::fromUtf8("noTitleLabel_1"));
        noTitleLabel_1->setGeometry(QRect(164, 22, 40, 17));
        noTitleLabel_1->setFont(font1);
        noTitleLabel_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        noValueLabel_1 = new QLabel(listWidget_1);
        noValueLabel_1->setObjectName(QString::fromUtf8("noValueLabel_1"));
        noValueLabel_1->setGeometry(QRect(210, 22, 60, 17));
        noValueLabel_1->setFont(font1);
        noValueLabel_1->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        listWidget_2 = new QWidget(resultWidget);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(0, 178, 282, 108));
        listWidget_2->setStyleSheet(QString::fromUtf8("image: 0;\n"
"background: 0;"));
        portraitLabel_2 = new QLabel(listWidget_2);
        portraitLabel_2->setObjectName(QString::fromUtf8("portraitLabel_2"));
        portraitLabel_2->setGeometry(QRect(12, 0, 144, 108));
        portraitLabel_2->setStyleSheet(QString::fromUtf8("background-color: rgb(158, 158, 158);\n"
"image: url(:/Images/\345\233\276\345\203\217_images19.png);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-color: rgb(0, 228, 255);"));
        rfidTitleLabel_2 = new QLabel(listWidget_2);
        rfidTitleLabel_2->setObjectName(QString::fromUtf8("rfidTitleLabel_2"));
        rfidTitleLabel_2->setGeometry(QRect(164, 0, 40, 17));
        rfidTitleLabel_2->setFont(font1);
        rfidTitleLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        rfidValueLabel_2 = new QLabel(listWidget_2);
        rfidValueLabel_2->setObjectName(QString::fromUtf8("rfidValueLabel_2"));
        rfidValueLabel_2->setGeometry(QRect(210, 0, 60, 17));
        rfidValueLabel_2->setFont(font1);
        rfidValueLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        posTitleLabel_2 = new QLabel(listWidget_2);
        posTitleLabel_2->setObjectName(QString::fromUtf8("posTitleLabel_2"));
        posTitleLabel_2->setGeometry(QRect(164, 44, 40, 17));
        posTitleLabel_2->setFont(font1);
        posTitleLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        posValueLabel_2 = new QLabel(listWidget_2);
        posValueLabel_2->setObjectName(QString::fromUtf8("posValueLabel_2"));
        posValueLabel_2->setGeometry(QRect(210, 44, 60, 17));
        posValueLabel_2->setFont(font1);
        posValueLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        timeTitlelabel_2 = new QLabel(listWidget_2);
        timeTitlelabel_2->setObjectName(QString::fromUtf8("timeTitlelabel_2"));
        timeTitlelabel_2->setGeometry(QRect(164, 66, 40, 17));
        timeTitlelabel_2->setFont(font1);
        timeTitlelabel_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        timeValueLabel_2 = new QLabel(listWidget_2);
        timeValueLabel_2->setObjectName(QString::fromUtf8("timeValueLabel_2"));
        timeValueLabel_2->setGeometry(QRect(210, 66, 60, 17));
        timeValueLabel_2->setFont(font1);
        timeValueLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        resultTitlelabel_2 = new QLabel(listWidget_2);
        resultTitlelabel_2->setObjectName(QString::fromUtf8("resultTitlelabel_2"));
        resultTitlelabel_2->setGeometry(QRect(164, 88, 40, 17));
        resultTitlelabel_2->setFont(font1);
        resultTitlelabel_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        resultValuelabel_2 = new QLabel(listWidget_2);
        resultValuelabel_2->setObjectName(QString::fromUtf8("resultValuelabel_2"));
        resultValuelabel_2->setGeometry(QRect(210, 88, 60, 17));
        resultValuelabel_2->setFont(font1);
        resultValuelabel_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        noTitleLabel_2 = new QLabel(listWidget_2);
        noTitleLabel_2->setObjectName(QString::fromUtf8("noTitleLabel_2"));
        noTitleLabel_2->setGeometry(QRect(164, 22, 40, 17));
        noTitleLabel_2->setFont(font1);
        noTitleLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        noValueLabel_2 = new QLabel(listWidget_2);
        noValueLabel_2->setObjectName(QString::fromUtf8("noValueLabel_2"));
        noValueLabel_2->setGeometry(QRect(210, 22, 60, 17));
        noValueLabel_2->setFont(font1);
        noValueLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        listWidget_3 = new QWidget(resultWidget);
        listWidget_3->setObjectName(QString::fromUtf8("listWidget_3"));
        listWidget_3->setGeometry(QRect(0, 306, 282, 108));
        listWidget_3->setStyleSheet(QString::fromUtf8("image: 0;\n"
"background: 0;"));
        portraitLabel_3 = new QLabel(listWidget_3);
        portraitLabel_3->setObjectName(QString::fromUtf8("portraitLabel_3"));
        portraitLabel_3->setGeometry(QRect(12, 0, 144, 108));
        portraitLabel_3->setStyleSheet(QString::fromUtf8("background-color: rgb(158, 158, 158);\n"
"image: url(:/Images/\345\233\276\345\203\217_images19.png);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-color: rgb(0, 228, 255);"));
        rfidTitleLabel_3 = new QLabel(listWidget_3);
        rfidTitleLabel_3->setObjectName(QString::fromUtf8("rfidTitleLabel_3"));
        rfidTitleLabel_3->setGeometry(QRect(164, 0, 40, 17));
        rfidTitleLabel_3->setFont(font1);
        rfidTitleLabel_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        rfidValueLabel_3 = new QLabel(listWidget_3);
        rfidValueLabel_3->setObjectName(QString::fromUtf8("rfidValueLabel_3"));
        rfidValueLabel_3->setGeometry(QRect(210, 0, 60, 17));
        rfidValueLabel_3->setFont(font1);
        rfidValueLabel_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        posTitleLabel_3 = new QLabel(listWidget_3);
        posTitleLabel_3->setObjectName(QString::fromUtf8("posTitleLabel_3"));
        posTitleLabel_3->setGeometry(QRect(164, 44, 40, 17));
        posTitleLabel_3->setFont(font1);
        posTitleLabel_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        posValueLabel_3 = new QLabel(listWidget_3);
        posValueLabel_3->setObjectName(QString::fromUtf8("posValueLabel_3"));
        posValueLabel_3->setGeometry(QRect(210, 44, 60, 17));
        posValueLabel_3->setFont(font1);
        posValueLabel_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        timeTitlelabel_3 = new QLabel(listWidget_3);
        timeTitlelabel_3->setObjectName(QString::fromUtf8("timeTitlelabel_3"));
        timeTitlelabel_3->setGeometry(QRect(164, 66, 40, 17));
        timeTitlelabel_3->setFont(font1);
        timeTitlelabel_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        timeValueLabel_3 = new QLabel(listWidget_3);
        timeValueLabel_3->setObjectName(QString::fromUtf8("timeValueLabel_3"));
        timeValueLabel_3->setGeometry(QRect(210, 66, 60, 17));
        timeValueLabel_3->setFont(font1);
        timeValueLabel_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        resultTitlelabel_3 = new QLabel(listWidget_3);
        resultTitlelabel_3->setObjectName(QString::fromUtf8("resultTitlelabel_3"));
        resultTitlelabel_3->setGeometry(QRect(164, 88, 40, 17));
        resultTitlelabel_3->setFont(font1);
        resultTitlelabel_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        resultValuelabel_3 = new QLabel(listWidget_3);
        resultValuelabel_3->setObjectName(QString::fromUtf8("resultValuelabel_3"));
        resultValuelabel_3->setGeometry(QRect(210, 88, 60, 17));
        resultValuelabel_3->setFont(font1);
        resultValuelabel_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        noValueLabel_3 = new QLabel(listWidget_3);
        noValueLabel_3->setObjectName(QString::fromUtf8("noValueLabel_3"));
        noValueLabel_3->setGeometry(QRect(210, 22, 60, 17));
        noValueLabel_3->setFont(font1);
        noValueLabel_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 228, 255);"));
        noTitleLabel_3 = new QLabel(listWidget_3);
        noTitleLabel_3->setObjectName(QString::fromUtf8("noTitleLabel_3"));
        noTitleLabel_3->setGeometry(QRect(164, 22, 40, 17));
        noTitleLabel_3->setFont(font1);
        noTitleLabel_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        dashSplitLabel_3 = new QLabel(resultWidget);
        dashSplitLabel_3->setObjectName(QString::fromUtf8("dashSplitLabel_3"));
        dashSplitLabel_3->setGeometry(QRect(12, 424, 258, 2));
        dashSplitLabel_3->setStyleSheet(QString::fromUtf8("image: 0;\n"
"background: 0;\n"
"border-width: 1px;\n"
"border-style: dashed;\n"
"border-color: rgb(0, 198, 255);"));
        videoWidget = new QWidget(centralwidget);
        videoWidget->setObjectName(QString::fromUtf8("videoWidget"));
        videoWidget->setGeometry(QRect(8, 55, 494, 535));
        videoWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/\345\267\246.png);"));
        videoLabel_x = new ReviewLabel(videoWidget);
        videoLabel_x->setObjectName(QString::fromUtf8("videoLabel_x"));
        videoLabel_x->setGeometry(QRect(12, 9, 470, 254));
        videoLabel_x->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background: 0;\n"
"background-color: rgb(158, 158, 158);\n"
""));
        videoLabel_s = new QLabel(videoWidget);
        videoLabel_s->setObjectName(QString::fromUtf8("videoLabel_s"));
        videoLabel_s->setGeometry(QRect(12, 272, 272, 254));
        videoLabel_s->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background: 0;\n"
"background-color: rgb(158, 158, 158);"));
        portraitLabel_s = new QLabel(videoWidget);
        portraitLabel_s->setObjectName(QString::fromUtf8("portraitLabel_s"));
        portraitLabel_s->setGeometry(QRect(290, 272, 192, 254));
        portraitLabel_s->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background: 0;\n"
"background-color: rgb(158, 158, 158);"));
        rfidWidget = new QWidget(videoWidget);
        rfidWidget->setObjectName(QString::fromUtf8("rfidWidget"));
        rfidWidget->setGeometry(QRect(290, 506, 192, 20));
        rfidWidget->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background: 0;\n"
"background-color:rgba(0,0,0,128)"));
        rfidLabel_1 = new QLabel(rfidWidget);
        rfidLabel_1->setObjectName(QString::fromUtf8("rfidLabel_1"));
        rfidLabel_1->setGeometry(QRect(4, 0, 80, 20));
        rfidLabel_1->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background: 0;\n"
"color: rgb(255,255,255);"));
        rfidLabel_2 = new QLabel(rfidWidget);
        rfidLabel_2->setObjectName(QString::fromUtf8("rfidLabel_2"));
        rfidLabel_2->setGeometry(QRect(100, 0, 80, 20));
        rfidLabel_2->setStyleSheet(QString::fromUtf8("image: 0;\n"
"border: 0;\n"
"background: 0;\n"
"color: rgb(255,255,255);"));
        stateNet = new QLabel(centralwidget);
        stateNet->setObjectName(QString::fromUtf8("stateNet"));
        stateNet->setGeometry(QRect(5, 25, 80, 14));
        stateNet->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:10px;background:transparent;color:#ff0000;"));
        stateCam_x = new QLabel(centralwidget);
        stateCam_x->setObjectName(QString::fromUtf8("stateCam_x"));
        stateCam_x->setGeometry(QRect(5, 10, 80, 14));
        stateCam_x->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:10px;background:transparent;color:#ff0000;"));
        stateCam_s = new QLabel(centralwidget);
        stateCam_s->setObjectName(QString::fromUtf8("stateCam_s"));
        stateCam_s->setGeometry(QRect(90, 10, 80, 14));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Microsoft Yahei"));
        stateCam_s->setFont(font2);
        stateCam_s->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:10px;background:transparent;color:#ff0000;"));
        stateBelt = new QLabel(centralwidget);
        stateBelt->setObjectName(QString::fromUtf8("stateBelt"));
        stateBelt->setGeometry(QRect(90, 25, 80, 14));
        stateBelt->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:10px;background:transparent;color:#ff0000;"));
        stateCam_x_2 = new QLabel(centralwidget);
        stateCam_x_2->setObjectName(QString::fromUtf8("stateCam_x_2"));
        stateCam_x_2->setGeometry(QRect(715, 10, 80, 14));
        stateCam_x_2->setStyleSheet(QString::fromUtf8("font-family: \"Microsoft Yahei\";font-size:10px;background:transparent;color:#00ff00;"));
        stateCam_x_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        meiTouLabel->setText(QString());
        titleLabel->setText(QApplication::translate("MainWindow", "\350\257\206        \345\210\253        \347\273\223        \346\236\234", nullptr));
        solidSplitLabel->setText(QString());
        dashSplitLabel_1->setText(QString());
        dashSplitLabel_2->setText(QString());
        portraitLabel_1->setText(QString());
        rfidTitleLabel_1->setText(QApplication::translate("MainWindow", "RFID\357\274\232", nullptr));
        rfidValueLabel_1->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        posTitleLabel_1->setText(QApplication::translate("MainWindow", "\344\275\215\347\275\256\357\274\232", nullptr));
        posValueLabel_1->setText(QApplication::translate("MainWindow", "\345\207\272X\345\205\211\346\234\272\345\217\243", nullptr));
        timeTitlelabel_1->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\357\274\232", nullptr));
        timeValueLabel_1->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        resultTitlelabel_1->setText(QApplication::translate("MainWindow", "\347\273\223\346\236\234\357\274\232", nullptr));
        resultValuelabel_1->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        noTitleLabel_1->setText(QApplication::translate("MainWindow", "\347\274\226\345\217\267\357\274\232", nullptr));
        noValueLabel_1->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        portraitLabel_2->setText(QString());
        rfidTitleLabel_2->setText(QApplication::translate("MainWindow", "RFID\357\274\232", nullptr));
        rfidValueLabel_2->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        posTitleLabel_2->setText(QApplication::translate("MainWindow", "\344\275\215\347\275\256\357\274\232", nullptr));
        posValueLabel_2->setText(QApplication::translate("MainWindow", "\345\207\272X\345\205\211\346\234\272\345\217\243", nullptr));
        timeTitlelabel_2->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\357\274\232", nullptr));
        timeValueLabel_2->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        resultTitlelabel_2->setText(QApplication::translate("MainWindow", "\347\273\223\346\236\234\357\274\232", nullptr));
        resultValuelabel_2->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        noTitleLabel_2->setText(QApplication::translate("MainWindow", "\347\274\226\345\217\267\357\274\232", nullptr));
        noValueLabel_2->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        portraitLabel_3->setText(QString());
        rfidTitleLabel_3->setText(QApplication::translate("MainWindow", "RFID\357\274\232", nullptr));
        rfidValueLabel_3->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        posTitleLabel_3->setText(QApplication::translate("MainWindow", "\344\275\215\347\275\256\357\274\232", nullptr));
        posValueLabel_3->setText(QApplication::translate("MainWindow", "\345\207\272X\345\205\211\346\234\272\345\217\243", nullptr));
        timeTitlelabel_3->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\357\274\232", nullptr));
        timeValueLabel_3->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        resultTitlelabel_3->setText(QApplication::translate("MainWindow", "\347\273\223\346\236\234\357\274\232", nullptr));
        resultValuelabel_3->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        noValueLabel_3->setText(QApplication::translate("MainWindow", "\342\200\224", nullptr));
        noTitleLabel_3->setText(QApplication::translate("MainWindow", "\347\274\226\345\217\267\357\274\232", nullptr));
        dashSplitLabel_3->setText(QString());
        videoLabel_x->setText(QString());
        videoLabel_s->setText(QString());
        portraitLabel_s->setText(QString());
        rfidLabel_1->setText(QString());
        rfidLabel_2->setText(QString());
        stateNet->setText(QApplication::translate("MainWindow", "\347\275\221\347\273\234\357\274\232\346\225\205\351\232\234", nullptr));
        stateCam_x->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\2641\357\274\232\346\225\205\351\232\234", nullptr));
        stateCam_s->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\2642\357\274\232\346\225\205\351\232\234", nullptr));
        stateBelt->setText(QApplication::translate("MainWindow", "\344\274\240\351\200\201\345\270\246\357\274\232\345\201\234\346\255\242", nullptr));
        stateCam_x_2->setText(QApplication::translate("MainWindow", "\347\211\210\346\234\254\345\217\267\357\274\232v1.0.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
