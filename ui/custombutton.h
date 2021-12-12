#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QString>
#include <QWidget>
#include <QPushButton>


class CustomButton : public QPushButton
{
public:
    CustomButton(QString btn_text, QWidget *parent = 0);
};

#endif // CUSTOMBUTTON_H
