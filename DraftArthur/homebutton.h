#ifndef HOMEBUTTON_H
#define HOMEBUTTON_H

#include <QPushButton>
#include <QObject>

class HomeButton : public QPushButton
{

    Q_OBJECT

public:
    HomeButton(QWidget *parent = nullptr);
    ~HomeButton();

};

#endif // HOMEBUTTON_H
