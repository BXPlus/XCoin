/********************************************************************************
** Form generated from reading UI file 'balancewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANCEWIDGET_H
#define UI_BALANCEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BalanceWidget
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *BalanceWidget)
    {
        if (BalanceWidget->objectName().isEmpty())
            BalanceWidget->setObjectName(QString::fromUtf8("BalanceWidget"));
        BalanceWidget->resize(815, 384);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        BalanceWidget->setFont(font);
        label = new QLabel(BalanceWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 60, 351, 71));
        label_2 = new QLabel(BalanceWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(340, 130, 201, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial Black"));
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        retranslateUi(BalanceWidget);

        QMetaObject::connectSlotsByName(BalanceWidget);
    } // setupUi

    void retranslateUi(QWidget *BalanceWidget)
    {
        BalanceWidget->setWindowTitle(QApplication::translate("BalanceWidget", "Form", nullptr));
        label->setText(QApplication::translate("BalanceWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">Your current Balance is :</span></p></body></html>", nullptr));
        label_2->setText(QApplication::translate("BalanceWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">21,02 XCoin</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BalanceWidget: public Ui_BalanceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANCEWIDGET_H
