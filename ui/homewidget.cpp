#include "homewidget.h"
#include <QLabel>
#include <QGraphicsWidget>
#include <QScrollArea>
#include <QScrollBar>

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent)
{
    pageLayout = new QVBoxLayout(this);

    title = new QLabel(this);
    title->setText("Welcome back!");
    title->setObjectName(QString("title"));
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    subtitle = new QLabel(this);
    subtitle->setText("Key #dk9174hdn57s");
    subtitle->setObjectName(QString("subtitle"));
    subtitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);




    //SCROLL AREA

    QWidget* accessBox = new QWidget(this);
    QScrollArea* scrollBox = new QScrollArea(accessBox);
    scrollBox->horizontalScrollBar()->setEnabled(false);
    scrollBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QBoxLayout* accessBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom, accessBox);
    accessBoxLayout->addWidget(scrollBox);
    accessBoxLayout->setAlignment(scrollBox, Qt::AlignHCenter);

    scrollBox->setStyleSheet("background-color: grey;");
    boxContainer = new QWidget(scrollBox);
    QVBoxLayout* boxLayout = new QVBoxLayout{boxContainer};
    //boxContainer->setLayout(boxLayout);
    scrollBox->setWidget(boxContainer);

    //boxContainer->resize(0.9*scrollBox->width(), 0.9*scrollBox->height());
    boxContainer->resize(1000, 1000);
    box1 = new QWidget(boxContainer);
    box2 = new QWidget(boxContainer);
    box3 = new QWidget(boxContainer);
    box4 = new QWidget(boxContainer);

    box1->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    box2->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    box3->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    box4->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    box1->setStyleSheet("border: 2px solid red;");
    box2->setStyleSheet("border: 2px solid yellow;");
    box3->setStyleSheet("border: 2px solid green;");
    box4->setStyleSheet("border: 2px solid purple;");

    boxLayout->addWidget(box1);
    boxLayout->addWidget(box2);
    boxLayout->addWidget(box3);
    boxLayout->addWidget(box4);







    // GRID BOX LAYOUT
//    boxContainer = new QWidget(this);
//    boxLayout = new QGridLayout(boxContainer);

//    box1 = new QWidget();
//    box2 = new QWidget();
//    box3 = new QWidget();
//    box4 = new QWidget();
//    box1->setStyleSheet("border: 2px solid red;");
//    box2->setStyleSheet("border: 2px solid yellow;");
//    box3->setStyleSheet("border: 2px solid green;");
//    box4->setStyleSheet("border: 2px solid purple;");
//    boxLayout->addWidget(box1, 0, 0);
//    boxLayout->addWidget(box2, 0, 1);
//    boxLayout->addWidget(box3, 1, 0);
//    boxLayout->addWidget(box4, 1, 1);


    pageLayout->addWidget(title);
    pageLayout->addWidget(subtitle);
    pageLayout->addWidget(accessBox); // change to boxContainer if grid box layout
    this->setLayout(pageLayout);

}

HomeWidget::~HomeWidget()
{
}
