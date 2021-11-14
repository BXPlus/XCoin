#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("XCoin");
    setMinimumSize(500,400);

    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    mainLayout = new QHBoxLayout(mainWidget);
    menuContainer = new QWidget(mainWidget);
    menuLayout = new QVBoxLayout(mainWidget);

    mainLayout->addWidget(menuContainer);

    QStringList titles = {"Home", "Contacts", "History", "Pay", "Live", "Graphics"};

}

MainWindow::~MainWindow()
{
    delete ui;
}

