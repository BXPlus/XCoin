#include "paybutton.h"

PayButton::PayButton(QWidget *parent)
    : QPushButton(parent)
{
    setText("Pay");
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

PayButton::~PayButton()
{

}
