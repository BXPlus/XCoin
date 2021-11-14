#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QObject>

class CustomButton : public QPushButton
{

    Q_OBJECT

public slots:

    void ActionDuBoutton();

public:
    CustomButton(QString text, QWidget *parent = 0);

    QString getName() {return m_text;}
    void setName(QString text) {m_text = text;}

    ~CustomButton();

private:
    QString m_text;
};

#endif // CUSTOMBUTTON_H
