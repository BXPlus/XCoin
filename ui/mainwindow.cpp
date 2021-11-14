#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <custombutton.h>
#include <QAction>
#include <QSignalMapper>
#include "logindialog.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Login page
    pop_login();

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
        btn->setCursor(Qt::PointingHandCursor);
        btnList.append(btn);
        menuLayout->addWidget(btn);
    }


    //Creating Stacked Widget
    contentContainer = new QStackedWidget(mainWidget);
    homeWidget = new QWidget(mainWidget);
    contentContainer->addWidget(homeWidget);
    balanceWidget = new QWidget(mainWidget);
    contentContainer->addWidget(balanceWidget);
    paymentsWidget = new QWidget(mainWidget);
    contentContainer->addWidget(paymentsWidget);
    contactsWidget = new QWidget(mainWidget);
    contentContainer->addWidget(contactsWidget);
    updatesWidget = new QWidget(mainWidget);
    contentContainer->addWidget(updatesWidget);
    graphsWidget = new QWidget(mainWidget);
    contentContainer->addWidget(graphsWidget);

    QStringList color_list = {"red", "yellow", "purple", "green", "white", "turquoise"};

    for (int i = 0; i < 6; i++){
        contentContainer->setCurrentIndex(i);
        QWidget* widget = contentContainer->currentWidget();
        QString style = QString("QWidget {border: 1px solid %1}").arg(color_list[i]);
        widget->setStyleSheet(style);

        QSignalMapper* signalMapper = new QSignalMapper (this) ;
        connect(btnList[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper -> setMapping (btnList[i], i);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(go_page(int)));
    }

    contentContainer->setCurrentIndex(0);

    // Creating main content
    mainLayout->addWidget(contentContainer);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::go_page(int i)
{
    contentContainer->setCurrentIndex(i);
}
void MainWindow::pop_login()

{
    LoginDialog dialogLogin;
    dialogLogin.setModal(true);
    dialogLogin.exec();
}
