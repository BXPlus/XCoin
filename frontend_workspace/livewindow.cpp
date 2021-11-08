#include "livewindow.h"
#include "ui_livewindow.h"

LiveWindow::LiveWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LiveWindow)
{
    ui->setupUi(this);
}

LiveWindow::~LiveWindow()
{
    delete ui;
}
