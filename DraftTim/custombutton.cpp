#include "custombutton.h"
#include <QDebug>

CustomButton::CustomButton(QString name, QWidget *parent)
    : QPushButton(parent)
{
    setText(name);
    if (name == "Login") {
        setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    }
    else {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    }
}
