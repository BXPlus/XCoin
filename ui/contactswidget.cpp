#include "contactswidget.h"
#include "mainwindow.h"
#include <QMap>
#include <QBoxLayout>
#include <QSignalMapper>
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

    //Add contact button creation
    addContactButton = new QPushButton(this);
    addContactButton->setText("Add Contact");
    addContactButton->setObjectName("ContactEdits");
    addContactButton->setCursor(Qt::PointingHandCursor);
    addContactButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    //Edit contact list button creation
    editBtn = new CustomButton("Edit", this);
    editBtn->setObjectName("ContactEdits");
    editBtn->setCursor(Qt::PointingHandCursor);
    editBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    connect(addContactButton, SIGNAL(clicked(bool)), this, SLOT(addContact()));
    connect(editBtn, SIGNAL(clicked(bool)), this, SLOT(editStyle()));

    topLayout->addWidget(title);
    topLayout->addWidget(addContactButton);
    topLayout->addWidget(editBtn);


    scrollContacts = new QScrollArea(this);
    boxContainer = new QWidget(scrollContacts);
    scrollContacts->setWidget(boxContainer);
    scrollContacts->setWidgetResizable(true);
    boxContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    contactGrid = new QGridLayout(boxContainer);
    contactGrid->setContentsMargins(0, 0, 0, 0);
    contactGrid->setSpacing(0);
    boxContainer->setObjectName("ScrollBox");

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
            key->setObjectName("keyContacts1");

            value->setObjectName("valueContacts1");
        }
        else{
            key->setObjectName("keyContacts2");
            value->setObjectName("valueContacts2");

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

void ContactsWidget::edit_contact()
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
            key->setObjectName("keyContacts1");
            value->setObjectName("valueContacts1");
        }
        else{
            key->setObjectName("keyContacts2");
            value->setObjectName("valueContacts2");
        }


        //Creation of delete buttons
        QPushButton* deleteBtn = new QPushButton("–", this);
        deleteBtn->setObjectName("deleteBtn");
        deleteBtn->setCursor(Qt::PointingHandCursor);
        deleteBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        delList.append(deleteBtn);

        //Connection of the buttons to deletion of the contact
        QSignalMapper* signalMapper = new QSignalMapper(this) ;
        connect(deleteBtn, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper->setMapping (deleteBtn, count);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(deleteContact(int)));

        QSignalMapper* signalMapper2 = new QSignalMapper(this) ;
        connect(deleteBtn, SIGNAL(clicked(bool)), signalMapper2, SLOT(map()));
        signalMapper2->setMapping (deleteBtn, key->text());
        connect(signalMapper2, SIGNAL(mapped(QString)), this, SLOT(get_key(QString)));

        //Put the buttons in the Layout
        QHBoxLayout* key_countainer = new QHBoxLayout();
        QWidget* key_widget = new QWidget();

        key_countainer->addWidget(deleteBtn);
        key_countainer->addWidget(key);
        key_widget->setLayout(key_countainer);

        contactGrid->addWidget(key_widget, count, 0);
        contactGrid->addWidget(value, count, 1);
    }
}

void ContactsWidget::addContact()
{
    addContactDialog* addDialog = new addContactDialog(this);
    addDialog->setModal(true);
    addDialog->exec();

    QList<QString> sList = addDialog->get_info();

    QString key = sList[1]+" "+sList[2];
    QString value = sList[3];

    if (sList[0] == "true") {
        if (key != " " && value != ""){
            contactDict[key] = value;
            delete_widgets();
            create_dictionnary();
        }
    }
}

void ContactsWidget::deleteContact(int count)
{
    contactGrid->removeWidget(contactGrid->itemAtPosition(count, 0)->widget());
    contactGrid->removeWidget(contactGrid->itemAtPosition(count, 1)->widget());
}

void ContactsWidget::editStyle()
{
    delete_widgets();

    if (editCount%2 == 0) {
        editBtn->setText("Done");
        edit_contact();
    }
    else {
        editBtn->setText("Edit");
        create_dictionnary();
    }
    editCount++;
}

void ContactsWidget::get_key(QString key_string)
{
    for (auto it = contactDict.begin(); it != contactDict.end(); it++)
        if (it.key() == key_string) {
            it = contactDict.erase(it);
            break;
        }
}


