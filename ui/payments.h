#ifndef PAYMENTS_H
#define PAYMENTS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>


namespace Ui {
class Payments;
}

class Payments : public QWidget
{
    Q_OBJECT

public:
    explicit Payments(QWidget *parent = nullptr);
    ~Payments();

    QWidget* page_container;
    QVBoxLayout* page_layout;
    QSizePolicy* Expanding;
private:
    Ui::Payments *ui;
};

#endif // PAYMENTS_H
