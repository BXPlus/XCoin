#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QStackedWidget>
#include <QComboBox>
#include <menuwidget.h>
#include <string>
#include <QtDebug>
#include <QList>
#include <menubtn.h>
#include <QStackedLayout>
#include <btncontainer.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("XCoin");
    setMinimumSize(500, 400);

    // Setting layouts
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    mainLayout = new QHBoxLayout(mainWidget);

    // creating two widgets for menu and contents
    QWidget* menuContainer = new QWidget(mainWidget);
    contentContainer = new QStackedWidget(mainWidget);
    mainLayout->addWidget(menuContainer);
    mainLayout->addWidget(contentContainer);

    // menu settings
    QVBoxLayout* menuLayout = new QVBoxLayout(menuContainer);
    menuContainer->setLayout(menuLayout);
    menuContainer->setMaximumWidth(200);

    QList<QPushButton *> btnList;

    for (int i=0; i<6; i++){

        QString t;
        if (i==0){t = "Home";}
        else if (i==1){t = "Contacts";}
        else if (i==2){t = "Balance History";}
        else if (i==3){t = "Pay";}
        else if (i==4){t = "Live";}
        else if (i==5){t = "Graphics";}

        BtnContainer *b = new BtnContainer(menuContainer);
        b->setStyleSheet("border: 2px solid red;");
        b->setMouseTracking(true);
        MenuBtn* btn = new MenuBtn(t, b);
        btnList.append(btn);
        btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        btn->setStyleSheet("QPushButton{border-radius: 30px;"
                           "border-width: 2px;"
                           "border: 2px solid pink;"
                           "text-align: left;"
                           "padding: 10px;}");
                           //"QPushButton:hover{background: rgba(75, 86, 124, 255)};");
        menuLayout->addWidget(btn);
    }

    // content settings

    //widgets creation
    QWidget *firstPageWidget = new QWidget;
    firstPageWidget->setStyleSheet("background-color: rgba(63,71,101,255);"
                                   "border-radius: 20px;");
    QWidget *secondPageWidget = new QWidget;
    secondPageWidget->setStyleSheet("background-color: blue;");
    QWidget *thirdPageWidget = new QWidget;
    thirdPageWidget->setStyleSheet("background-color: green;");
    QWidget *fourthPageWidget = new QWidget;
    fourthPageWidget->setStyleSheet("background-color: black;");
    QWidget *fifthPageWidget = new QWidget;
    fifthPageWidget->setStyleSheet("background-color: white;");

    // stacked layout creation
    //QStackedLayout *stackedLayout = new QStackedLayout;

    // list containing widgets
    QList<QWidget *> pageList;
    pageList.append(firstPageWidget);
    pageList.append(secondPageWidget);
    pageList.append(thirdPageWidget);
    pageList.append(fourthPageWidget);
    pageList.append(fifthPageWidget);

    int j = 0;
    for (QList<QWidget *>::iterator i=pageList.begin(); i!=pageList.end(); i++){
        contentContainer->addWidget(*i);
        //stackedLayout->addWidget(*i);
        j ++;
    }


//    connect(pageComboBox, QOverload<int>::of(&QComboBox::activated),
//            contentContainer, &QStackedWidget::setCurrentIndex);

    // debugging and stylesheets
    this->setStyleSheet("background-color: rgba(75,92,154,255);");
    menuContainer->setStyleSheet("border: 20px solid blue;"
                                 "background-color: rgba(92,104,151,255);");

}

MainWindow::~MainWindow()
{
    delete ui;
}
