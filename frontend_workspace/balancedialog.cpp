#include "balancedialog.h"
#include "ui_balancedialog.h"

BalanceDialog::BalanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BalanceDialog)
{
    ui->setupUi(this);
}

BalanceDialog::~BalanceDialog()
{
    delete ui;
}
