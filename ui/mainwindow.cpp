#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <custombutton.h>
#include <QAction>
#include <QSignalMapper>
#include <QLabel>
#include <QDir>
#include <paymentdialog.h>
#include <purchase_xcoin.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("XCoin");
    setMinimumSize(700,600);


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


    // Creating userBlock

    QWidget* userBlock = new QWidget(menuContainer);
    QVBoxLayout* userBlockLayout = new QVBoxLayout(userBlock);
    userBlock->setFixedHeight(150);
    userBlock->setStyleSheet("border-radius: 15px;"
                              "background-color: rgba(50, 79, 126, 255);");

    // XCoin logo
    QString path = QDir::currentPath();
    int index = path.indexOf("XCoin");
    QString subPath = path.mid(0,index+5);
    subPath.append("/ui/xcoin.jpg");

    QPixmap pic(subPath);
    QLabel* imgLabel = new QLabel(userBlock);
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

    QStringList titles = {"Home", "Contacts", "Pay", "History", "Live", "Graphics"};

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
    paymentsWidget = new Purchase_XCoin(mainWidget);
    contentContainer->addWidget(paymentsWidget);
    contactsWidget = new QWidget(mainWidget);
    contentContainer->addWidget(contactsWidget);
    updatesWidget = new QWidget(mainWidget);
    contentContainer->addWidget(updatesWidget);
    graphsWidget = new QWidget(mainWidget);
    contentContainer->addWidget(graphsWidget);

    QStringList color_list = {"red", "yellow", "pink", "green", "white", "turquoise"};

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

    QPushButton* pay_btn = new QPushButton(QString("PAY NOW"), mainWidget);
        pay_btn->setMinimumSize(100,100);
        pay_btn->setStyleSheet("border-radius: 10px;"
                               "background-color: green;");
        connect(pay_btn, &QPushButton::released, this, &MainWindow::on_pushButton_clicked);


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

void MainWindow::on_pushButton_clicked()
{
    PaymentDialog payment_window;
    payment_window.setModal(true);
    payment_window.exec();
}
