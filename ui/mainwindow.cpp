#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <custombutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("XCoin");
    setMinimumSize(500,400);


    // Setting layouts
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    mainLayout = new QHBoxLayout(mainWidget);


    // Creating menu
    menuContainer = new QWidget(mainWidget);
    menuLayout = new QVBoxLayout(menuContainer);
    menuContainer->setLayout(menuLayout);
    mainLayout->addWidget(menuContainer);
    menuContainer->setMaximumWidth(200);

    QStringList titles = {"Home", "Contacts", "History", "Pay", "Live", "Graphics"};

    for (int i=0; i<6; i++){

        CustomButton* btn = new CustomButton(titles[i], menuContainer);
        btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        btn->setStyleSheet("QPushButton{border-radius: 30px;"
                           "border-width: 2px;"
                           "border: 2px solid pink;"
                           "text-align: left;"
                           "padding: 10px;"
                           "margin: 0;}");
                           //"QPushButton:hover{background: rgba(75, 86, 124, 255)};");
        menuLayout->addWidget(btn);
    }



    // Creating main content
    contentContainer = new QStackedWidget(mainWidget);
    mainLayout->addWidget(contentContainer);



}

MainWindow::~MainWindow()
{
    delete ui;
}

