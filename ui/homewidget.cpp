#include "homewidget.h"
#include <QLabel>
#include <QGraphicsWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QFontDatabase>
#include <QDir>

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent)
{
    pageLayout = new QVBoxLayout(this);
    pageLayout->setAlignment(Qt::AlignCenter);

    title = new QLabel(this);
    title->setText("Welcome back.");
    title->setObjectName(QString("title"));
    title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    // logo
    QString path = QDir::currentPath();
    int index = path.indexOf("XCoin");
    QString subPath = path.mid(0,index+5);
    subPath.append("/ui/xcoinBig.jpg");

    QPixmap pic(subPath);
    QLabel* imgLabel = new QLabel(this);
    imgLabel->setAlignment(Qt::AlignCenter);
    //imgLabel->setFixedSize(50, 50);
    imgLabel->setPixmap(pic);

    // Uncomment to add subtitle
//    subtitle = new QLabel(this);
//    subtitle->setText("Key #dk9174hdn57s");
//    subtitle->setObjectName(QString("subtitle"));
//    subtitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);




    //SCROLL AREA

//    QWidget* accessBox = new QWidget(this);
//    QScrollArea* scrollBox = new QScrollArea(accessBox);
//    scrollBox->horizontalScrollBar()->setEnabled(false);
//    scrollBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    QBoxLayout* accessBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom, accessBox);
//    accessBoxLayout->addWidget(scrollBox);
//    accessBoxLayout->setAlignment(scrollBox, Qt::AlignHCenter);

//    scrollBox->setStyleSheet("background-color: grey;");
//    boxContainer = new QWidget(scrollBox);
//    QVBoxLayout* boxLayout = new QVBoxLayout{boxContainer};
//    //boxContainer->setLayout(boxLayout);
//    scrollBox->setWidget(boxContainer);

//    //boxContainer->resize(0.9*scrollBox->width(), 0.9*scrollBox->height());
//    boxContainer->resize(1000, 1000);
//    box1 = new QWidget(boxContainer);
//    box2 = new QWidget(boxContainer);
//    box3 = new QWidget(boxContainer);
//    box4 = new QWidget(boxContainer);

//    box1->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    box2->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    box3->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    box4->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

//    box1->setStyleSheet("border: 2px solid red;");
//    box2->setStyleSheet("border: 2px solid yellow;");
//    box3->setStyleSheet("border: 2px solid green;");
//    box4->setStyleSheet("border: 2px solid purple;");

//    boxLayout->addWidget(box1);
//    boxLayout->addWidget(box2);
//    boxLayout->addWidget(box3);
//    boxLayout->addWidget(box4);







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

//    // box 1: XCoin
//    QVBoxLayout* box1Layout = new QVBoxLayout(box1);
//    box1->setLayout(box1Layout);
//    QWidget* chart1 = new QWidget(box1);
//    chart1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    chart1->setStyleSheet("background-color: white;");
//    box1Layout->addWidget(chart1);

//    // box 2: XCoin
//    QVBoxLayout* box2Layout = new QVBoxLayout(box2);
//    box2->setLayout(box2Layout);
//    QWidget* chart2 = new QWidget(box2);
//    chart2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    chart2->setStyleSheet("background-color: blue;");
//    box2Layout->addWidget(chart2);

//    // box 3: XCoin
//    QVBoxLayout* box3Layout = new QVBoxLayout(box3);
//    box3->setLayout(box3Layout);
//    QWidget* chart3 = new QWidget(box3);
//    chart3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    chart3->setStyleSheet("background-color: yellow;");
//    box3Layout->addWidget(chart3);

//    // box 4: XCoin
//    QVBoxLayout* box4Layout = new QVBoxLayout(box4);
//    box4->setLayout(box4Layout);
//    QWidget* chart4 = new QWidget(box4);
//    chart4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    chart4->setStyleSheet("background-color: red;");
//    box4Layout->addWidget(chart4);


    pageLayout->addWidget(imgLabel);
    pageLayout->addWidget(title);
    //pageLayout->addWidget(subtitle);
    //pageLayout->addWidget(boxContainer); // change to boxContainer or accessBox if grid box layout or scroll area, uncomment if want widget
    this->setLayout(pageLayout);

}

HomeWidget::~HomeWidget()
{
}
