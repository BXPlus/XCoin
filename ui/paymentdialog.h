#ifndef PAYMENTDIALOG_H
#define PAYMENTDIALOG_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class PaymentDialog;
}

class PaymentDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PaymentDialog(QWidget *parent = nullptr);
    ~PaymentDialog();
    QLabel* title_page_label;
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


//I add this for the pay_btn QPushButton
private slots:
    void handlepay_btn();

private:
    Ui::PaymentDialog *ui;
};

#endif // PAYMENTDIALOG_H
