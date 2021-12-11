/********************************************************************************
** Form generated from reading UI file 'paymentdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAYMENTDIALOG_H
#define UI_PAYMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaymentDialog
{
public:

    void setupUi(QWidget *PaymentDialog)
    {
        if (PaymentDialog->objectName().isEmpty())
            PaymentDialog->setObjectName(QString::fromUtf8("PaymentDialog"));
        PaymentDialog->resize(400, 300);

        retranslateUi(PaymentDialog);

        QMetaObject::connectSlotsByName(PaymentDialog);
    } // setupUi

    void retranslateUi(QWidget *PaymentDialog)
    {
        PaymentDialog->setWindowTitle(QApplication::translate("PaymentDialog", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaymentDialog: public Ui_PaymentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYMENTDIALOG_H
