#include "contactbutton.h"

ContactButton::ContactButton(QWidget *parent)
    : QPushButton(parent)
{
    setText("Contact");
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

ContactButton::~ContactButton()
{

}
