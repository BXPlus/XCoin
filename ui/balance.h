#ifndef BALANCE_H
#define BALANCE_H

#include <QWidget>

namespace Ui {
class Balance;
}

class Balance : public QWidget
{
    Q_OBJECT

public:
    explicit Balance(QWidget *parent = nullptr);
    ~Balance();

private:
    Ui::Balance *ui;
};

#endif // BALANCE_H
