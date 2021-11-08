#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnContacts, SIGNAL(clicked()), this, SLOT(contacts()));
}

void MainWindow::contacts(){
    contact_animation = new QPropertyAnimation(ui->btnContacts, "geometry");
    contact_animation->setDuration(10000);
    contact_animation->setStartValue(ui->btnContacts->geometry());
    contact_animation->setEndValue(QRect(200, 200, 100, 50));
    contact_animation->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnBalance_clicked()
{
    //BalanceDialog balancedial;
    //balancedial.setModal(true);
    //balancedial.exec();
    hide();
    balancedial = new BalanceDialog(this);
    balancedial->show();
}


void MainWindow::on_btnPay_clicked()
{
    hide();
    paywindow = new PayWindow(this);
    paywindow->show();
}

