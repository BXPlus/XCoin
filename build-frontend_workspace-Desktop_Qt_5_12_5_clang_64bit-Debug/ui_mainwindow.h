/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
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
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(767, 401);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0.273, stop:0 rgba(255, 228, 225, 255), stop:1 rgba(224, 255, 255, 255));\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnContacts = new QPushButton(centralwidget);
        btnContacts->setObjectName(QString::fromUtf8("btnContacts"));
        btnContacts->setGeometry(QRect(100, 240, 102, 102));
        btnContacts->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 240, 102, 102));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(230, 270, 102, 102));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(470, 240, 102, 102));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(590, 240, 102, 102));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btnContacts->setText(QApplication::translate("MainWindow", "Contacts", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Pay", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Balance", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "Live", nullptr));
        pushButton_5->setText(QApplication::translate("MainWindow", "Graphs and Stats", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
