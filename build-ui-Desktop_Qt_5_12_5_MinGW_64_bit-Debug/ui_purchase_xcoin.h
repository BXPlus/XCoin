/********************************************************************************
** Form generated from reading UI file 'purchase_xcoin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PURCHASE_XCOIN_H
#define UI_PURCHASE_XCOIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Purchase_XCoin
{
public:

    void setupUi(QWidget *Purchase_XCoin)
    {
        if (Purchase_XCoin->objectName().isEmpty())
            Purchase_XCoin->setObjectName(QString::fromUtf8("Purchase_XCoin"));
        Purchase_XCoin->resize(400, 300);

        retranslateUi(Purchase_XCoin);

        QMetaObject::connectSlotsByName(Purchase_XCoin);
    } // setupUi

    void retranslateUi(QWidget *Purchase_XCoin)
    {
        Purchase_XCoin->setWindowTitle(QApplication::translate("Purchase_XCoin", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Purchase_XCoin: public Ui_Purchase_XCoin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PURCHASE_XCOIN_H
