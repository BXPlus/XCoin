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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BalanceWidget
{
public:

    void setupUi(QWidget *BalanceWidget)
    {
        if (BalanceWidget->objectName().isEmpty())
            BalanceWidget->setObjectName(QString::fromUtf8("BalanceWidget"));
        BalanceWidget->resize(815, 384);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        BalanceWidget->setFont(font);

        retranslateUi(BalanceWidget);

        QMetaObject::connectSlotsByName(BalanceWidget);
    } // setupUi

    void retranslateUi(QWidget *BalanceWidget)
    {
        BalanceWidget->setWindowTitle(QApplication::translate("BalanceWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BalanceWidget: public Ui_BalanceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANCEWIDGET_H
