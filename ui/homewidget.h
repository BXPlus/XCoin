#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include "../XNode/node.h"
#include "../XNode/XNodeSDK.h"

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
private:
    void handleNewNodeStatusFromSDK(XNodeSDK::XNodeStatus status);
};

#endif // HOMEWIDGET_H
