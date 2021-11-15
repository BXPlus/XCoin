#include "balancewidget.h"
#include "ui_balancewidget.h"

BalanceWidget::BalanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BalanceWidget)
{
    ui->setupUi(this);
}

BalanceWidget::~BalanceWidget()
{
    delete ui;
}
