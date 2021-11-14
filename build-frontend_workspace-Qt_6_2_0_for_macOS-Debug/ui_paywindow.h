/********************************************************************************
** Form generated from reading UI file 'paywindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAYWINDOW_H
#define UI_PAYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PayWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;

    void setupUi(QMainWindow *PayWindow)
    {
        if (PayWindow->objectName().isEmpty())
            PayWindow->setObjectName(QString::fromUtf8("PayWindow"));
        PayWindow->resize(856, 611);
        centralwidget = new QWidget(PayWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 20, 121, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        pushButton->setFont(font);
        PayWindow->setCentralWidget(centralwidget);

        retranslateUi(PayWindow);

        QMetaObject::connectSlotsByName(PayWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PayWindow)
    {
        PayWindow->setWindowTitle(QCoreApplication::translate("PayWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("PayWindow", "Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PayWindow: public Ui_PayWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYWINDOW_H
