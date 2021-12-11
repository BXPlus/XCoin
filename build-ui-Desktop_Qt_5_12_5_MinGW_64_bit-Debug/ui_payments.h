/********************************************************************************
** Form generated from reading UI file 'payments.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAYMENTS_H
#define UI_PAYMENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Payments
{
public:

    void setupUi(QWidget *Payments)
    {
        if (Payments->objectName().isEmpty())
            Payments->setObjectName(QString::fromUtf8("Payments"));
        Payments->resize(400, 300);

        retranslateUi(Payments);

        QMetaObject::connectSlotsByName(Payments);
    } // setupUi

    void retranslateUi(QWidget *Payments)
    {
        Payments->setWindowTitle(QApplication::translate("Payments", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Payments: public Ui_Payments {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYMENTS_H
