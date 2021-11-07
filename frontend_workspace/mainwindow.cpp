#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    animation = new QPropertyAnimation(ui->pushButton, "geometry");
    animation->setDuration(10000);
    animation->setStartValue(ui->pushButton->geometry());
    animation->setEndValue(QRect(200, 200, 100, 50));
    animation->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

