#ifndef CONTACTBUTTON_H
#define CONTACTBUTTON_H

#include <QPushButton>
#include <QObject>

class ContactButton : public QPushButton
{

    Q_OBJECT

public:
    ContactButton(QWidget *parent = nullptr);
    ~ContactButton();
};

#endif // CONTACTBUTTON_H
