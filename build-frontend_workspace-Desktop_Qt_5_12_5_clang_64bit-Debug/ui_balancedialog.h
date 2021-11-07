/********************************************************************************
** Form generated from reading UI file 'balancedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANCEDIALOG_H
#define UI_BALANCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_BalanceDialog
{
public:

    void setupUi(QDialog *BalanceDialog)
    {
        if (BalanceDialog->objectName().isEmpty())
            BalanceDialog->setObjectName(QString::fromUtf8("BalanceDialog"));
        BalanceDialog->resize(400, 300);

        retranslateUi(BalanceDialog);

        QMetaObject::connectSlotsByName(BalanceDialog);
    } // setupUi

    void retranslateUi(QDialog *BalanceDialog)
    {
        BalanceDialog->setWindowTitle(QApplication::translate("BalanceDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BalanceDialog: public Ui_BalanceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANCEDIALOG_H
