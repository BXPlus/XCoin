#include "paywidget.h"
#include <QDebug>

PayWidget::PayWidget(QWidget *parent)
    : QWidget{parent}
{
    pageLayout = new QVBoxLayout(this);
    pageLayout->setAlignment(Qt::AlignTop);

    // load Contacts dictionary later
    contactDict[QString("John Lennon")] = QString("04bfcab8722991ae774db48f934ca79cfb7dd991229153b9f732ba5334aafcd8e7266e47076996b55a14bf9913ee3145ce0cfc1372ada8ada74bd287450313534a");
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
    contactDict[QString("Hassiba le C")] = QString("undecipherable key");

    topBox = new QWidget();
    topLayout = new QHBoxLayout();
    topBox->setLayout(topLayout);

    title = new QLabel(this);
    title->setText("Pay");
    title->setObjectName(QString("title"));
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    contactSearch = new QLineEdit(this);
    contactSearch->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    contactSearch->setPlaceholderText("Search");
    connect(contactSearch, &QLineEdit::textEdited, this, &PayWidget::contactSearchEdit);

    topLayout->addWidget(title);
    topLayout->addWidget(contactSearch);

    scrollContacts = new QScrollArea(this);
    boxContainer = new QWidget(scrollContacts);
    scrollContacts->setWidget(boxContainer);
    scrollContacts->setWidgetResizable(true);
    scrollContacts->setStyleSheet("background-color: rgba(31,41,66,255);");
    boxContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    contactGrid = new QGridLayout(boxContainer);
    contactGrid->setContentsMargins(0, 0, 0, 0);
    contactGrid->setSpacing(0);

    create_dictionary(contactDict);

    pageLayout->addWidget(topBox);
    pageLayout->addWidget(scrollContacts);
}

void PayWidget::create_dictionary(QMap<QString, QString> contacts)
{
    for(auto e : contacts.keys())
    {
        QLabel* key = new QLabel;
        key->setText(e);
        QLabel* value = new QLabel;
        value->setText(contactDict.value(e));
        value->setWordWrap(true);
        value->setMaximumWidth(200);
        key->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        value->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        key->setObjectName("key");
        int count = contactGrid->rowCount();

        QPushButton* coverRowBtn = new QPushButton(key);
        coverRowBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        //coverRowBtn->setFlat(true);
        coverRowBtn->setCursor(Qt::PointingHandCursor);
        coverRowBtn->setObjectName("coverRowBtn");

        //Connection of the pay button to opening a dialog for paying this specific contact
        QSignalMapper* signalMapper = new QSignalMapper(this);
        connect(coverRowBtn, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(coverRowBtn, key->text());
        connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(openPayDialog(QString)));

        if (count%2 == 1){
            coverRowBtn->setStyleSheet("QPushButton#coverRowBtn{background-color: rgba(255,255,255,0);}"
                                       "QPushButton#coverRowBtn:hover{background-color: rgba(211, 229, 255, 20);}");
            key->setStyleSheet("background-color: rgba(60, 72, 114, 255);"
                               "padding: 20;"
                               "font: 15px;");
            value->setStyleSheet("background-color: rgba(60, 72, 114, 255);"
                                 "padding: 20;"
                                 "font: 15px;");
        }
        else{
            coverRowBtn->setStyleSheet("QPushButton#coverRowBtn{background-color: rgba(255,255,255,0);}"
                                       "QPushButton#coverRowBtn:hover{background-color: rgba(211, 229, 255, 20);}");
            key->setStyleSheet("background-color: rgba(31,41,66,255);"
                               "padding: 20;"
                               "font: 15px;");
            value->setStyleSheet("background-color: rgba(31,41,66,255);"
                                 "padding: 20;"
                                 "font: 15px;");
        }

        contactGrid->addWidget(key, count, 0);
        contactGrid->addWidget(value, count, 1);
        contactGrid->addWidget(coverRowBtn, count, 0, 1, 2);
        //contactGrid->addWidget(payButton, count, 2);
    }
}

void PayWidget::contactSearchEdit(){
    QString* text = new QString(contactSearch->text().toLower());
    QMap<QString, QString> tempContacts;
    deleteWidgets();
    for (auto e : contactDict.keys()){
        if ((e.toLower().contains(text)) or contactDict.value(e).contains(text)){
            tempContacts[e] = contactDict.value(e);
        }
    }
    create_dictionary(tempContacts);
}

void PayWidget::deleteContact(int count)
{
    contactGrid->removeWidget(contactGrid->itemAtPosition(count, 0)->widget());
    contactGrid->removeWidget(contactGrid->itemAtPosition(count, 1)->widget());
}

void PayWidget::openPayDialog(QString value){
    payContactDialog* dialog = new payContactDialog(value, this);
    dialog->setModal(true);
    dialog->exec();
}

void PayWidget::deleteWidgets()
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








