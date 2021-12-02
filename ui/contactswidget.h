#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class ContactsWidget;
}

class ContactsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContactsWidget(QWidget *parent = nullptr);
    QLabel* title;
};

#endif // CONTACTSWIDGET_H
