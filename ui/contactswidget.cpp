#include "contactswidget.h"
#include <QMap>
#include <QDebug>

ContactsWidget::ContactsWidget(QWidget *parent) :
    QWidget(parent)
{
    pageLayout = new QVBoxLayout(this);
    pageLayout->setAlignment(Qt::AlignTop);

    // load Contacts dictionary later
    QMap<QString, QString> contactDict;
    contactDict[QString("John Lennon")] = QString("#dk9174hdn57s");
    contactDict[QString("Bob")] = QString("#dk9174hdn29s");
    contactDict[QString("Alex")] = QString("#dk9174hdn57s");
    contactDict[QString("Clara")] = QString("#dk9174hdn29s");
    contactDict[QString("Picha")] = QString("#dk9174hdn57s");
    contactDict[QString("Tim")] = QString("#dk9174hdn29s");
    contactDict[QString("Cyrus")] = QString("#dk9174hdn57s");
    contactDict[QString("Arthur")] = QString("#dk9174hdn29s");
    contactDict[QString("Youssef")] = QString("#dk9174hdn57s");
    contactDict[QString("Mamoune")] = QString("#dk9174hdn29s");
    //int n = contactDict.count();

    title = new QLabel(this);
    title->setText("Contacts");
    title->setObjectName(QString("title"));
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    boxContainer = new QWidget(this);
    boxContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    contactGrid = new QGridLayout(boxContainer);
    contactGrid->setContentsMargins(0, 0, 0, 0);
    contactGrid->setSpacing(0);

    for(auto e : contactDict.keys())
    {
        QLabel* key = new QLabel;
        key->setText(e);
        QLabel* value = new QLabel;
        value->setText(contactDict.value(e));
        key->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        value->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        int count = contactGrid->rowCount();
        if (count%2 == 0){
            key->setStyleSheet("background-color: rgba(60, 72, 114, 255);"
                               "padding: 20;"
                               "font: 15px;");
            value->setStyleSheet("background-color: rgba(60, 72, 114, 255);"
                                 "padding: 20;"
                                 "font: 15px;");
        }
        else{
            key->setStyleSheet("padding: 20;"
                               "font: 15px;");
            value->setStyleSheet("padding: 20;"
                                 "font: 15px;");
        }
        contactGrid->addWidget(key, count, 0);
        contactGrid->addWidget(value, count, 1);
    }

    pageLayout->addWidget(title);
    pageLayout->addWidget(boxContainer);

}
