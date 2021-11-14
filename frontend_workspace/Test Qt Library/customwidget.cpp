#include "customwidget.h"
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.setPen(Qt::black);

    p.setBrush(m_isClicked ? Qt::red : Qt::gray);
    p.drawRoundedRect(20,20, this->width()-40, this->height()-40, 20,20);

    p.setPen(Qt::white);
    p.drawText(this->width() * 0.5f - 30,this->height() * 0.5f,"ToutApprendre");

    updateGeometry();
}

void CustomWidget::mousePressEvent(QMouseEvent *e)
{
    m_isClicked = true;
    repaint();
}

void CustomWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_isClicked = false;
    repaint();
}
