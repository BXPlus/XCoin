#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QObject>

class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    CustomButton(QString name, QWidget *parent = 0);
};

#endif // CUSTOMBUTTON_H
