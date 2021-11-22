#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>

namespace Ui {
class HomeWidget;
}

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);
    QVBoxLayout* pageLayout;
    QWidget* boxContainer;
    QGridLayout* boxLayout;
    QLabel* title;
    QLabel* subtitle;
    QWidget* box1;
    QWidget* box2;
    QWidget* box3;
    QWidget* box4;

    ~HomeWidget();
};

#endif // HOMEWIDGET_H
