#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <custombutton.h>
#include <QAction>
#include <QSignalMapper>
#include <QLabel>
#include <QDir>
#include <QCloseEvent>
#include <QFontDatabase>
#include <paymentdialog.h>
#include <purchase_xcoin.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //HomePage setup
    setWindowTitle("XCoin");
    setMinimumSize(700,600);


    // Setting layouts
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);


    // Creating menu
    menuContainer = new QWidget(mainWidget);
    menuLayout = new QVBoxLayout(menuContainer);
    menuContainer->setLayout(menuLayout);
    mainLayout->addWidget(menuContainer);
    menuContainer->setMaximumWidth(200);
    menuContainer->setObjectName("menuContainer");
    menuContainer->setContentsMargins(0,0,0,0);


    // Creating userBlock

    QWidget* userBlock = new QWidget(menuContainer);
    QVBoxLayout* userBlockLayout = new QVBoxLayout(userBlock);
    userBlockLayout->setAlignment(Qt::AlignHCenter);
    userBlock->setFixedHeight(150);
    userBlock->setStyleSheet("border-radius: 15px;"
                              "background-color: rgba(60, 72, 114, 255);");

    // XCoin logo
    QString path = QDir::currentPath();
    int index = path.indexOf("XCoin");
    QString subPath = path.mid(0,index+5);
    subPath.append("/ui/xcoinSmall.png");

    QPixmap pic(subPath);
    QLabel* imgLabel = new QLabel(userBlock);
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setFixedSize(50, 50);
    imgLabel->setPixmap(pic);

    // XCoin title
    QLabel* titleLabel = new QLabel(userBlock);
    titleLabel->setText("XCoin");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setMaximumHeight(30);

    // User Balance
    QLabel* balanceLabel = new QLabel(userBlock);
    balanceLabel->setText("964.52");
    balanceLabel->setAlignment(Qt::AlignCenter);
    balanceLabel->setStyleSheet("background-color: rgba(98, 130, 184, 255);"
                                "border-radius: 10px;"
                                "margin: 0;");
    balanceLabel->setMaximumHeight(30);

    userBlockLayout->addWidget(imgLabel);
    userBlockLayout->addWidget(titleLabel);
    userBlockLayout->addWidget(balanceLabel);

    menuLayout->addWidget(userBlock);

    // Creating remaining buttons
    QStringList titles = {"Home", "Contacts", "Pay", "History", "Settings", "Graphics"};

    for (int i=0; i<6; i++){

        CustomButton* btn = new CustomButton(titles[i], menuContainer);
        btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        btn->setFixedWidth(100);
        btn->setCursor(Qt::PointingHandCursor);
        btnList.append(btn);
        btn->setObjectName("menuBtn");
        menuLayout->addWidget(btn);
    }


    // Creating central separating bar
//    QWidget* sepBar = new QWidget(this);
//    sepBar->setStyleSheet("background-color: rgba(45,58,82,255);");
//    sepBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
//    sepBar->setFixedWidth(10);
//    mainLayout->addWidget(sepBar);


    //Creating Stacked Widget

    contentContainer = new QStackedWidget(mainWidget);
    contentContainer->setObjectName("contentContainer");

    homeWidget = new HomeWidget(mainWidget);
    contentContainer->addWidget(homeWidget);
    contactsWidget = new ContactsWidget(mainWidget);
    contentContainer->addWidget(contactsWidget);
    balanceWidget = new QWidget(mainWidget);
    contentContainer->addWidget(balanceWidget);
    paymentsWidget = new Purchase_XCoin(mainWidget);
    contentContainer->addWidget(paymentsWidget);
    settingsWidget = new SettingsWidget(mainWidget);
    contentContainer->addWidget(settingsWidget);
    graphsWidget = new QWidget(mainWidget);
    contentContainer->addWidget(graphsWidget);

    for (int i = 0; i < 6; i++){
        QSignalMapper* signalMapper = new QSignalMapper (this) ;
        connect(btnList[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper->setMapping (btnList[i], i);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(go_page(int)));
    }

//    QPushButton* pay_btn = new QPushButton(QString("PAY NOW"), mainWidget);
//        pay_btn->setMinimumSize(100,100);
//        pay_btn->setStyleSheet("border-radius: 10px;"
//                               "background-color: green;");
//        connect(pay_btn, &QPushButton::released, this, &MainWindow::on_pushButton_clicked);


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

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::go_home()
{
    contentContainer->setCurrentIndex(0);
}
void MainWindow::on_pushButton_clicked()
{
    PaymentDialog payment_window;
    payment_window.setModal(true);
    payment_window.exec();
}
