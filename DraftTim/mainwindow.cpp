#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    dialog_login = new Login();
    pop_login();
    ui->setupUi(this);
    setWindowTitle("XCoin");
    QStringList menu_list = {"Home", "Balance", "Payments", "Contacts", "Updates", "Graphs"};
    QStringList color_list = {"red", "yellow", "purple", "green", "white", "turquoise"};
    ListPages = {home_widget, balance_widget, payments_widget, contacts_widget, updates_widget,
                graphs_widget};

    m_widget = new QWidget(this);
    m_swidget = new QStackedWidget(m_widget);
    hbtn_widget = new QWidget(m_widget);

    int j = 0;
    for(QList<QWidget*>::iterator i = ListPages.begin(); i != ListPages.end(); ++i) {
        *i = new QWidget(m_widget);
        m_swidget->addWidget(*i);
        j ++;
    }

    og_layout = new QVBoxLayout(m_widget);
    hbtn_layout = new QHBoxLayout(hbtn_widget);
//    home_layout = new QHBoxLayout(home_widget);
//    balance_layout = new QHBoxLayout(balance_widget);
//    payments_layout = new QHBoxLayout(payments_widget);
//    contacts_layout = new QHBoxLayout(contacts_widget);
//    updates_layout = new QHBoxLayout(updates_widget);
//    graphs_layout = new QHBoxLayout(graphs_widget);

//    hbtn_widget->setLayout(hbtn_layout);
//    home_widget->setLayout(home_layout);
//    balance_widget->setLayout(balance_layout);
//    payments_widget->setLayout(payments_layout);
//    contacts_widget->setLayout(contacts_layout);
//    updates_widget->setLayout(updates_layout);
//    graphs_widget->setLayout(graphs_layout);

//    home_widget->setStyleSheet("QWidget {border: 1px solid red}");
//    balance_widget->setStyleSheet("QWidget {border: 1px solid yellow}");
//    payments_widget->setStyleSheet("QWidget {border: 1px solid purple}");
//    contacts_widget->setStyleSheet("QWidget {border: 1px solid green}");
//    updates_widget->setStyleSheet("QWidget {border: 1px solid white}");
//    graphs_widget->setStyleSheet("QWidget {border: 1px solid turquoise}");

    m_swidget->setCurrentIndex(0);

    og_layout->addWidget(m_swidget, 93);
    og_layout->addWidget(hbtn_widget, 7);
    m_widget->setLayout(og_layout);

    for (int i = 0; i < 6; i++) {
            CustomButton* btn = new CustomButton(menu_list[i], m_widget);
            ListBtn.append(btn);
            hbtn_layout->addWidget(btn);
    }

    connect(ListBtn[0], SIGNAL(clicked(bool)), this, SLOT(go_home()));
    connect(ListBtn[1], SIGNAL(clicked(bool)), this, SLOT(go_balance()));
    connect(ListBtn[2], SIGNAL(clicked(bool)), this, SLOT(go_payments()));
    connect(ListBtn[3], SIGNAL(clicked(bool)), this, SLOT(go_contacts()));
    connect(ListBtn[4], SIGNAL(clicked(bool)), this, SLOT(go_updates()));
    connect(ListBtn[5], SIGNAL(clicked(bool)), this, SLOT(go_graphs()));

    setCentralWidget(m_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::go_home()
{
    m_swidget->setCurrentIndex(0);
}

void MainWindow::go_balance()
{
    m_swidget->setCurrentIndex(1);
}

void MainWindow::go_payments()
{
    m_swidget->setCurrentIndex(2);
}

void MainWindow::go_contacts()
{
    m_swidget->setCurrentIndex(3);
}

void MainWindow::go_updates()
{
    m_swidget->setCurrentIndex(4);
}

void MainWindow::go_graphs()
{
    m_swidget->setCurrentIndex(5);
}

bool MainWindow::pop_login()
{
    dialog_login->setModal(true);
    dialog_login->exec();
}
