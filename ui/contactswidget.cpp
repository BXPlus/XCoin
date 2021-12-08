#include "contactswidget.h"
#include <QMap>
#include <QDebug>
#include <QScrollArea>
#include <QScrollBar>
#include <QSignalMapper>

ContactsWidget::ContactsWidget(QWidget *parent) :
    QWidget(parent)
{
    pageLayout = new QVBoxLayout(this);
    pageLayout->setAlignment(Qt::AlignTop);

    // load Contacts dictionary later
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
    contactDict[QString("Long")] = QString("#dk9174hdn29s");
    contactDict[QString("JS")] = QString("#dk9174hdn29s");
    contactDict[QString("Laura")] = QString("#dk9174hdn29s");
    contactDict[QString("Lio")] = QString("#dk9174hdn29s");
    contactDict[QString("Timothé")] = QString("#dk9174hdn29s");
    contactDict[QString("Salma")] = QString("#dk9174hdn29s");

    topBox = new QWidget();
    topLayout = new QHBoxLayout();
    topBox->setLayout(topLayout);

    title = new QLabel(this);
    title->setText("Contacts");
    title->setObjectName(QString("title"));
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    addContactButton = new QPushButton(this);
    addContactButton->setText("Add Contact");
    addContactButton->setObjectName("menuBtn");
    addContactButton->setCursor(Qt::PointingHandCursor);
    addContactButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    connect(addContactButton, SIGNAL(clicked(bool)), this, SLOT(addContact()));

    topLayout->addWidget(title);
    topLayout->addWidget(addContactButton);


    scrollContacts = new QScrollArea(this);
    boxContainer = new QWidget(scrollContacts);
    scrollContacts->setWidget(boxContainer);
    scrollContacts->setWidgetResizable(true);
    boxContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    contactGrid = new QGridLayout(boxContainer);
    contactGrid->setContentsMargins(0, 0, 0, 0);
    contactGrid->setSpacing(0);

    create_dictionnary();

    pageLayout->addWidget(topBox);
    pageLayout->addWidget(scrollContacts);

}

void ContactsWidget::create_dictionnary()
{
    for(auto e : contactDict.keys())
    {
        QLabel* key = new QLabel;
        key->setText(e);
        QLabel* value = new QLabel;
        value->setText(contactDict.value(e));
        key->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        value->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        int count = contactGrid->rowCount();
        if (count%2 == 1){
            key->setStyleSheet("background-color: rgba(60, 72, 114, 255);"
                               "padding: 20;"
                               "font: 15px;"
                               "border-top-left-radius: 5px;"
                               "border-bottom-left-radius: 5px;");
            value->setStyleSheet("background-color: rgba(60, 72, 114, 255);"
                                 "padding: 20;"
                                 "font: 15px;");
        }
        else{
            key->setStyleSheet("background-color: rgba(31,41,66,255);"
                               "padding: 20;"
                               "font: 15px;"
                               "border-top-left-radius: 5px;"
                               "border-bottom-left-radius: 5px;");
            value->setStyleSheet("background-color: rgba(31,41,66,255);"
                                 "padding: 20;"
                                 "font: 15px;");
        }
        contactGrid->addWidget(key, count, 0);
        contactGrid->addWidget(value, count, 1);
    }
}

void ContactsWidget::delete_widgets()
{
    if ( contactGrid != NULL )
    {
        QLayoutItem* item;
        while ( ( item = contactGrid->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
}

void ContactsWidget::addContact()
{
    addContactDialog* addDialog = new addContactDialog(this);
    addDialog->setModal(true);
    addDialog->exec();

    QList<QString> sList = addDialog->get_info();

    if (sList[0] == "true") {
        QString key = sList[1]+" "+sList[2];
        QString value = sList[3];
        contactDict[key] = value;

        delete_widgets();
        create_dictionnary();
    }
}


