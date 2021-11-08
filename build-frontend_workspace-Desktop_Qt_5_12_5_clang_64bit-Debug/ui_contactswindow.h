/********************************************************************************
** Form generated from reading UI file 'contactswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTSWINDOW_H
#define UI_CONTACTSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContactsWindow
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *ContactsWindow)
    {
        if (ContactsWindow->objectName().isEmpty())
            ContactsWindow->setObjectName(QString::fromUtf8("ContactsWindow"));
        ContactsWindow->resize(856, 611);
        centralwidget = new QWidget(ContactsWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ContactsWindow->setCentralWidget(centralwidget);

        retranslateUi(ContactsWindow);

        QMetaObject::connectSlotsByName(ContactsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ContactsWindow)
    {
        ContactsWindow->setWindowTitle(QApplication::translate("ContactsWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ContactsWindow: public Ui_ContactsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTSWINDOW_H
