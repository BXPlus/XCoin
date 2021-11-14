#ifndef BTNCONTAINER_H
#define BTNCONTAINER_H

#include <QWidget>

class BtnContainer : public QWidget
{
    Q_OBJECT
public:
    explicit BtnContainer(QWidget *parent = nullptr);

private:
    void mouseMoveEvent(QMouseEvent *e);

};

#endif // BTNCONTAINER_H
