#ifndef BALANCEWIDGET_H
#define BALANCEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class BalanceWidget;
}

class BalanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BalanceWidget(QWidget *parent = nullptr);
    ~BalanceWidget();
    QWidget* balanceWidget;
    QWidget* transacContainer;
    QHBoxLayout* hbalanceLayout;
    QVBoxLayout* vbalanceLayout;
    QVBoxLayout* transacLayout;

private:
    Ui::BalanceWidget *ui;
};

#endif // BALANCEWIDGET_H
