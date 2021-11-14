#include "btncontainer.h"
#include <QDebug>
#include <QPushButton>

BtnContainer::BtnContainer(QWidget *parent) : QWidget(parent)
{
}

void BtnContainer::mouseMoveEvent(QMouseEvent *e){
    qDebug() << "hi";
//    QPushButton* button = findChild<QPushButton*>("Home");
//    button->setStyleSheet("QPushButton{border-radius: 30px;"
//                          "border-width: 2px;"
//                          "border: 2px solid pink;"
//                          "text-align: left;"
//                          "padding: 10px;"
//                          "background-color: white;}");
    //this->setStyleSheet("background-color: white;");
}
