#ifndef PAYMENTS_H
#define PAYMENTS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


namespace Ui {
class Payments;
}

class Payments : public QWidget
{
    Q_OBJECT

public:
    explicit Payments(QWidget *parent = nullptr);
    ~Payments();
    QLabel* title_page_label;
    QWidget* purchasing_box;
    QVBoxLayout* purchasing_layout;
    QWidget* amount_box;
    QVBoxLayout* amount_layout;
    QLabel* amount;
    QWidget* money_value_box ;
    QHBoxLayout* money_value_layout;
    QWidget* currency;
    QPushButton* pay_btn;

//I add this for the pay_btn QPushButton
private slots:
    void handlepay_btn();

private:
    Ui::Payments *ui;
};

#endif // PAYMENTS_H
