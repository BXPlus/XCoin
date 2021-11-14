#include "livebutton.h"

LiveButton::LiveButton(QWidget *parent)
    : QPushButton(parent)
{
    setText("Live Stats");
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

LiveButton::~LiveButton()
{

}
