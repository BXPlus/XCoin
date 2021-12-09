#ifndef PURCHASE_XCOIN_H
#define PURCHASE_XCOIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class Purchase_XCoin;
}

class Purchase_XCoin : public QWidget
{
    Q_OBJECT

public:
    explicit Purchase_XCoin(QWidget *parent = nullptr);
    ~Purchase_XCoin();

    QWidget* main_box;
    QVBoxLayout* main_layout;
    QWidget* amount_box;
    QVBoxLayout* amount_layout;
    QLabel* amount;
    QWidget* money_value_box ;
    QHBoxLayout* money_value_layout;
    QWidget* currency;
    QPushButton* XCO2;
    QPushButton* pay_btn;

private:
    Ui::Purchase_XCoin *ui;
};

#endif // PURCHASE_XCOIN_H
