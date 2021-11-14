#ifndef GRAPHBUTTON_H
#define GRAPHBUTTON_H

#include <QPushButton>
#include <QObject>

class GraphButton : public QPushButton
{

    Q_OBJECT

public:
    GraphButton(QWidget *parent = nullptr);
    ~GraphButton();
};

#endif // GRAPHBUTTON_H
