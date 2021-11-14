#ifndef LIVEBUTTON_H
#define LIVEBUTTON_H

#include <QPushButton>
#include <QObject>

class LiveButton : public QPushButton
{

    Q_OBJECT

public:
    LiveButton(QWidget *parent = nullptr);
    ~LiveButton();
};

#endif // LIVEBUTTON_H
