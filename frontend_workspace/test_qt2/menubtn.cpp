#include "menubtn.h"
#include <string>
#include <QDebug>

MenuBtn::MenuBtn(QString btn_text, QWidget *parent)
{
    const QString t = btn_text;
    setText(t);
}

void MenuBtn::isclicked(){
    qDebug() << "Jean Serrat";
    //contentContainer->setCurrentIndex(j);
}
