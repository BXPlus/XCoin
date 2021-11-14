#include "homebutton.h"

HomeButton::HomeButton(QWidget *parent)
    : QPushButton(parent)
{
    setText("Home");
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

HomeButton::~HomeButton()
{

}
