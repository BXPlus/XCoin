/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnContacts;
    QPushButton *btnPay;
    QPushButton *btnBalance;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(856, 611);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0.273, stop:0 rgba(255, 228, 225, 255), stop:1 rgba(224, 255, 255, 255));\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnContacts = new QPushButton(centralwidget);
        btnContacts->setObjectName(QString::fromUtf8("btnContacts"));
        btnContacts->setGeometry(QRect(200, 250, 102, 102));
        btnContacts->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"position: absolute;\n"
"background-color:  rgba(186, 85, 211, 220);\n"
"border-style: solid;\n"
"border-width:1px;\n"
"border-radius:26px;\n"
"border-color: rgba(255,0,255,100);\n"
"max-width:100px;\n"
"max-height:100px;\n"
"min-width:100px;\n"
"min-height:100px;\n"
"}"));
        btnPay = new QPushButton(centralwidget);
        btnPay->setObjectName(QString::fromUtf8("btnPay"));
        btnPay->setGeometry(QRect(320, 160, 102, 102));
        btnPay->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"position: absolute;\n"
"background-color:  rgba(186, 85, 211, 220);\n"
"border-style: solid;\n"
"border-width:1px;\n"
"border-radius:50px;\n"
"border-color: rgba(255,0,255,100);\n"
"max-width:100px;\n"
"max-height:100px;\n"
"min-width:100px;\n"
"min-height:100px;\n"
"}"));
        btnBalance = new QPushButton(centralwidget);
        btnBalance->setObjectName(QString::fromUtf8("btnBalance"));
        btnBalance->setGeometry(QRect(200, 60, 102, 102));
        btnBalance->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"position: absolute;\n"
"background-color:  rgba(186, 85, 211, 220);\n"
"border-style: solid;\n"
"border-width:1px;\n"
"border-radius:26px;\n"
"border-color: rgba(255,0,255,100);\n"
"max-width:100px;\n"
"max-height:100px;\n"
"min-width:100px;\n"
"min-height:100px;\n"
"}"));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(450, 60, 102, 102));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"position: absolute;\n"
"background-color:  rgba(186, 85, 211, 220);\n"
"border-style: solid;\n"
"border-width:1px;\n"
"border-radius:26px;\n"
"border-color: rgba(255,0,255,100);\n"
"max-width:100px;\n"
"max-height:100px;\n"
"min-width:100px;\n"
"min-height:100px;\n"
"}"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(440, 240, 102, 102));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color:  rgba(186, 85, 211, 220);\n"
"border-style: solid;\n"
"border-width:1px;\n"
"border-radius:26px;\n"
"border-color: rgba(255,0,255,100);\n"
"max-width:100px;\n"
"max-height:100px;\n"
"min-width:100px;\n"
"min-height:100px;\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnContacts->setText(QCoreApplication::translate("MainWindow", "Contacts", nullptr));
        btnPay->setText(QCoreApplication::translate("MainWindow", "Pay", nullptr));
        btnBalance->setText(QCoreApplication::translate("MainWindow", "Balance", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Live", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Graphs and Stats", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
