#ifndef MENUBTN_H
#define MENUBTN_H
#include <string>
#include <QPushButton>

class MenuBtn : public QPushButton
{
public:
    MenuBtn(QString btn_text, QWidget *parent = 0);
private slots:
    void isclicked();
};

#endif // MENUBTN_H
