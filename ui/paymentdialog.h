#ifndef PAYMENTDIALOG_H
#define PAYMENTDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class PaymentDialog;
}

class PaymentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentDialog(QDialog *parent = nullptr);
    ~PaymentDialog();
    QLabel* title_page_label;
    QWidget* pay_box;
    QVBoxLayout* pay_layout;
    QWidget* amount_box;
    QVBoxLayout* amount_layout;
    QLabel* amount;
    QWidget* money_value_box ;
    QHBoxLayout* money_value_layout;
    QWidget* currency;
    QPushButton* XCO2;
    QPushButton* pay_btn;


private:
    Ui::PaymentDialog *ui;
};

#endif // PAYMENTDIALOG_H
