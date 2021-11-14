#include "graphbutton.h"

GraphButton::GraphButton(QWidget *parent)
    : QPushButton(parent)
{
    setText("Graphs");
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

GraphButton::~GraphButton()
{

}
