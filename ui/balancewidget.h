#ifndef BALANCEWIDGET_H
#define BALANCEWIDGET_H

#include <QWidget>

namespace Ui {
class BalanceWidget;
}

class BalanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BalanceWidget(QWidget *parent = nullptr);
    ~BalanceWidget();

private:
    Ui::BalanceWidget *ui;
};

#endif // BALANCEWIDGET_H
