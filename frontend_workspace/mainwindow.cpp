#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnPay_clicked()
{
    hide();
    paywindow = new PayWindow(this);
    paywindow->show();
}


void MainWindow::on_btnBalance_clicked()
{
    hide();
    balancewindow = new BalanceWindow(this);
    balancewindow->show();
}


void MainWindow::on_btnContacts_clicked()
{
    hide();
    contactswindow = new ContactsWindow(this);
    contactswindow->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    hide();
    livewindow = new LiveWindow(this);
    livewindow->show();
}



void MainWindow::on_pushButton_5_clicked()
{
    hide();
    graphwindow = new GraphWindow(this);
    graphwindow->show();
}

