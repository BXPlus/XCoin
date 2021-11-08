/********************************************************************************
** Form generated from reading UI file 'paywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAYWINDOW_H
#define UI_PAYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PayWindow
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *PayWindow)
    {
        if (PayWindow->objectName().isEmpty())
            PayWindow->setObjectName(QString::fromUtf8("PayWindow"));
        PayWindow->resize(856, 611);
        centralwidget = new QWidget(PayWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PayWindow->setCentralWidget(centralwidget);

        retranslateUi(PayWindow);

        QMetaObject::connectSlotsByName(PayWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PayWindow)
    {
        PayWindow->setWindowTitle(QApplication::translate("PayWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PayWindow: public Ui_PayWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYWINDOW_H
