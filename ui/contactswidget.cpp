#include "contactswidget.h"
#include <QMap>
#include <QDebug>

ContactsWidget::ContactsWidget(QWidget *parent) :
    QWidget(parent)
{
    pageLayout = new QVBoxLayout(this);

    // load Contacts dictionary later
    QMap<QString, QString> contactDict;
    contactDict[QString("John Lennon")] = QString("#dk9174hdn57s");
    contactDict[QString("Bob")] = QString("#dk9174hdn29s");
    int n = contactDict.count();

    title = new QLabel(this);
    title->setText("Contacts");
    title->setObjectName(QString("title"));
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    boxContainer = new QWidget(this);
    contactGrid = new QGridLayout(boxContainer);

    for(auto e : contactDict.keys())
    {
        QLabel* key = new QLabel;
        key->setText(e);
        QLabel* value = new QLabel;
        value->setText(contactDict.value(e));
        int count = contactGrid->rowCount();
        contactGrid->addWidget(key, count, 0);
        contactGrid->addWidget(value, count, 1);
    }

    pageLayout->addWidget(title);
    pageLayout->addWidget(boxContainer);

}
