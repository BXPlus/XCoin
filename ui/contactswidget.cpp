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
    contactDict[QString("Alex")] = QString("04bfcab8722991ae774db48f934ca79cfb7dd991229153b9f732ba5334aafcd8e7266e47076996b55a14bf9913ee3145ce0cfc1372ada8ada74bd287450313534a");
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
    addContactButton->setText("Add");
    addContactButton->setObjectName("ContactEdits");
    addContactButton->setCursor(Qt::PointingHandCursor);
    addContactButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    //Edit contact list button creation
    editBtn = new CustomButton("Edit", this);
    editBtn->setObjectName("ContactEdits");
    editBtn->setCursor(Qt::PointingHandCursor);
    editBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    //Search contact QLineEdit creation
    contactSearch = new QLineEdit(this);
    contactSearch->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    contactSearch->setPlaceholderText("Search...");
    contactSearch->setFocus();
    contactSearch->setStyleSheet("QLineEdit{margin: 5px;"
                                 "padding: 10px;"
                                 "color: white;"
                                 "selection-color: white;"
                                 "background: rgba(157, 204, 255, 150);"
                                 "border: 1px solid rgba(255, 255, 255, 0);"
                                 "border-color: white;"
                                 "border-radius: 10px;}");
    contactSearch->setAttribute(Qt::WA_MacShowFocusRect, 0);

    connect(addContactButton, SIGNAL(clicked(bool)), this, SLOT(addContact()));
    connect(editBtn, SIGNAL(clicked(bool)), this, SLOT(editStyle()));
    connect(contactSearch, &QLineEdit::textEdited, this, &ContactsWidget::contactSearchEdit);

    topLayout->addWidget(title);
    topLayout->addWidget(addContactButton);
    topLayout->addWidget(editBtn);
    topLayout->addWidget(contactSearch);

    scrollContacts = new QScrollArea(this);
    boxContainer = new QWidget(scrollContacts);
    scrollContacts->setWidget(boxContainer);
    scrollContacts->setWidgetResizable(true);
    boxContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    contactGrid = new QGridLayout(boxContainer);
    contactGrid->setContentsMargins(0, 0, 0, 0);
    contactGrid->setSpacing(0);
    boxContainer->setObjectName("ScrollBox");

    createDictionary(contactDict);

    pageLayout->addWidget(topBox);
    pageLayout->addWidget(scrollContacts);

}

void ContactsWidget::createDictionary(QMap<QString, QString> contacts)
{
    for(auto e : contacts.keys())
    {
        QLabel* key = new QLabel;
        key->setText(e);
        QLabel* value = new QLabel;
        value->setText(contactDict.value(e));
        value->setWordWrap(true);
        key->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        //value->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        //value->setFixedSize(QLabel::sizeHint());
        int count = contactGrid->rowCount();

        QPushButton* coverRowBtn = new QPushButton(key);
        coverRowBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        coverRowBtn->setCursor(Qt::PointingHandCursor);
        coverRowBtn->setObjectName("coverRowBtn");

        QSignalMapper* signalMapper = new QSignalMapper(this);
        connect(coverRowBtn, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(coverRowBtn, key->text());
        connect(signalMapper, SIGNAL(mappedString(QString)), this, SLOT(openPayDialog(QString)));

        if (count%2 == 1){
            coverRowBtn->setStyleSheet("QPushButton#coverRowBtn{background-color: rgba(255,255,255,0);}"
                                       "QPushButton#coverRowBtn:hover{background-color: rgba(211, 229, 255, 20);}");
            key->setObjectName("keyContacts1");
            value->setObjectName("valueContacts1");
        }
        else{
            coverRowBtn->setStyleSheet("QPushButton#coverRowBtn{background-color: rgba(255,255,255,0);}"
                                       "QPushButton#coverRowBtn:hover{background-color: rgba(211, 229, 255, 20);}");
            key->setObjectName("keyContacts2");
            value->setObjectName("valueContacts2");
        }
        contactGrid->addWidget(key, count, 0);
        contactGrid->addWidget(value, count, 1);
        contactGrid->addWidget(coverRowBtn, count, 0, 1, 2);
    }
}

void ContactsWidget::editContact()
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
        //delList.append(deleteBtn);

        //Connection of the buttons to deletion of the contact
        QSignalMapper* signalMapper = new QSignalMapper(this) ;
        connect(deleteBtn, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper->setMapping (deleteBtn, count);
        connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(deleteContact(int)));

        QSignalMapper* signalMapper2 = new QSignalMapper(this) ;
        connect(deleteBtn, SIGNAL(clicked(bool)), signalMapper2, SLOT(map()));
        signalMapper2->setMapping (deleteBtn, key->text());
        connect(signalMapper2, SIGNAL(mappedString(QString)), this, SLOT(get_key(QString)));

        contactGrid->addWidget(deleteBtn, count, 0);
        contactGrid->addWidget(key, count, 1);
        contactGrid->addWidget(value, count, 2);
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
            deleteWidgets();
            createDictionary(contactDict);
        }
    }
}

void ContactsWidget::editStyle(){
    deleteWidgets();

    if (editCount == 0) {
        editBtn->setText("Done");
        editContact();
        editCount ++;
    }
    else {
        editBtn->setText("Edit");
        createDictionary(contactDict);
        editCount--;
    }
}

void ContactsWidget::deleteContact(int count){
    contactGrid->removeWidget(contactGrid->itemAtPosition(count, 0)->widget());
    contactGrid->removeWidget(contactGrid->itemAtPosition(count, 1)->widget());
    contactGrid->removeWidget(contactGrid->itemAtPosition(count, 2)->widget());
}

void ContactsWidget::get_key(QString key_string){
    for (auto it = contactDict.begin(); it != contactDict.end(); it++){
        if (it.key() == key_string) {
            it = contactDict.erase(it);
            break;
        }
    }
    editContact();
}

void ContactsWidget::contactSearchEdit(){
    QString* text = new QString(contactSearch->text().toLower());
    QMap<QString, QString> tempContacts;
    deleteWidgets();
    for (auto e : contactDict.keys()){
        if (e.toLower().contains(*text) || contactDict.value(e).contains(*text)){
            tempContacts[e] = contactDict.value(e);
        }
    }
    createDictionary(tempContacts);
}

void ContactsWidget::openPayDialog(QString value){
    payContactDialog* dialog = new payContactDialog(value, this);
    dialog->setModal(true);
    dialog->exec();
}

void ContactsWidget::deleteWidgets()
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

