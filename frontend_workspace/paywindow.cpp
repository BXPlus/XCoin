#include "paywindow.h"
#include "ui_paywindow.h"
#include "main.cpp"

PayWindow::PayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PayWindow)
{
    ui->setupUi(this);
}

PayWindow::~PayWindow()
{
    delete ui;
}

void PayWindow::on_pushButton_clicked()
{
    hide();
    main(0, nullptr);
}

