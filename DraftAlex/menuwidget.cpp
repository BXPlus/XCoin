#include "menuwidget.h"
#include <QPainter>
#include <QDebug>
#include <string>

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void MenuWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::darkCyan);
    painter.drawRoundedRect(30, 30, this->width()-60, this->height()-60, 30, 30);
}

void MenuWidget::setText(std::string text){

}
