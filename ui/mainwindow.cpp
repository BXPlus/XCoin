#include "mainwindow.h"
#include <QStringList>
#include "custombutton.h"
#include <QAction>
#include <QSignalMapper>
#include <QLabel>
#include <QDir>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    userBlock->setObjectName("UserBlock");

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

    userBalance = 0;

    xcoin::Node::getInstance().getSdkInstance()->onLocalBalanceChanged = std::bind( &MainWindow::updateUserBalanceFromSDK, this, std::placeholders::_1 );

    // User Balance
    balanceLabel = new QLabel(userBlock);
    balanceLabel->setText(QString::number(userBalance));
    balanceLabel->setAlignment(Qt::AlignCenter);
    balanceLabel->setObjectName("BalanceLabel");
    balanceLabel->setMaximumHeight(30);

    userBlockLayout->addWidget(imgLabel);
    userBlockLayout->addWidget(titleLabel);
    userBlockLayout->addWidget(balanceLabel);

    menuLayout->addWidget(userBlock);

    // Creating remaining buttons
    QStringList titles = {"Home", "Contacts", "Balance", "Settings"};

    for (int i=0; i<4; i++){

        CustomButton* btn = new CustomButton(titles[i], menuContainer);
        btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        btn->setFixedWidth(100);
        btn->setCursor(Qt::PointingHandCursor);
        btnList.append(btn);
        btn->setObjectName("menuBtn");
        menuLayout->addWidget(btn);
    }


    //Creating Stacked Widget

    contentContainer = new QStackedWidget(mainWidget);
    contentContainer->setObjectName("contentContainer");

    homeWidget = new HomeWidget(mainWidget);
    contentContainer->addWidget(homeWidget);
    contactsWidget = new ContactsWidget(mainWidget);
    contentContainer->addWidget(contactsWidget);
    balanceWidget = new BalanceWidget(mainWidget);
    balanceWidget->setObjectName("BalanceWidget");
    contentContainer->addWidget(balanceWidget);
    settingsWidget = new SettingsWidget(mainWidget);
    contentContainer->addWidget(settingsWidget);

    for (int i = 0; i < 4; i++){
        QSignalMapper* signalMapper = new QSignalMapper (this) ;
        connect(btnList[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper->setMapping (btnList[i], i);
        connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(go_page(int)));
    }

    contentContainer->setCurrentIndex(0);

    // Creating main content

    mainLayout->addWidget(contentContainer);
}

MainWindow::~MainWindow()
{
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

void MainWindow::toggleStyleSheet(){
    if (style == 0) {
        menuContainer->setStyleSheet("background-color: rgba(255,255,255,255);");
        style = 1;
    }
    else if (style == 1) {
        menuContainer->setStyleSheet("background-color: rgba(34,45,72,255);");
        style = 0;
    }
}

int MainWindow::getUserBalance() {
    return userBalance;
}

void MainWindow::editUserBalance(int inc, int dec) {
    if (inc > 0) {
        userBalance = userBalance + inc;
    }
    if (dec > 0) {
        userBalance = userBalance - dec;
    }
    balanceLabel->setText(QString::number(userBalance));
}

void MainWindow::updateUserBalanceFromSDK(int newBalance) {
    userBalance = newBalance;
    balanceLabel->setText(QString::number(userBalance));
    balanceWidget->updateBalanceSDKChange(newBalance);
}