#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <iostream>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);
    void setText(std::string text);

protected:
    void paintEvent(QPaintEvent *event);
    //void mousePressEvent(QMouseEvent* e);
    //void MouseReleaseEvent(QMouseEvent* e);
};

#endif // MENUWIDGET_H
