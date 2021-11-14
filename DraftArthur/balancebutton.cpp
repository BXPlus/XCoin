#include "balancebutton.h"

BalanceButton::BalanceButton(QWidget *parent)
    : QPushButton(parent)
{
    setText("Balance");
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

BalanceButton::~BalanceButton()
{

}
