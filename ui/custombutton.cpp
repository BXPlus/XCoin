#include "custombutton.h"

CustomButton::CustomButton(QString btn_text, QWidget *parent)
{
    const QString t = btn_text;
    setText(t);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}
