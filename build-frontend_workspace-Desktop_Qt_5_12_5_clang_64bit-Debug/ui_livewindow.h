/********************************************************************************
** Form generated from reading UI file 'livewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVEWINDOW_H
#define UI_LIVEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LiveWindow
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *LiveWindow)
    {
        if (LiveWindow->objectName().isEmpty())
            LiveWindow->setObjectName(QString::fromUtf8("LiveWindow"));
        LiveWindow->resize(856, 611);
        centralwidget = new QWidget(LiveWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LiveWindow->setCentralWidget(centralwidget);

        retranslateUi(LiveWindow);

        QMetaObject::connectSlotsByName(LiveWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LiveWindow)
    {
        LiveWindow->setWindowTitle(QApplication::translate("LiveWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LiveWindow: public Ui_LiveWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVEWINDOW_H
