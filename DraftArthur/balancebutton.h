#ifndef BALANCEBUTTON_H
#define BALANCEBUTTON_H

#include <QPushButton>
#include <QObject>

class BalanceButton : public QPushButton
{

    Q_OBJECT

public:
    BalanceButton(QWidget *parent = nullptr);
    ~BalanceButton();
};

#endif // BALANCEBUTTON_H
