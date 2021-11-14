#ifndef PAYBUTTON_H
#define PAYBUTTON_H

#include <QPushButton>
#include <QObject>

class PayButton : public QPushButton
{

    Q_OBJECT

public:
    PayButton(QWidget *parent = nullptr);
    ~PayButton();
};

#endif // PAYBUTTON_H
