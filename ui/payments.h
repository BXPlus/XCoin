#ifndef PAYMENTS_H
#define PAYMENTS_H

#include <QWidget>

namespace Ui {
class Payments;
}

class Payments : public QWidget
{
    Q_OBJECT

public:
    explicit Payments(QWidget *parent = nullptr);
    ~Payments();

private:
    Ui::Payments *ui;
};

#endif // PAYMENTS_H
