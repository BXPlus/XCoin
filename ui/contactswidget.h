#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>

namespace Ui {
class ContactsWidget;
}

class ContactsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContactsWidget(QWidget *parent = nullptr);
    QLabel* title;
    QVBoxLayout* pageLayout;
    QGridLayout* contactGrid;
    QWidget* boxContainer;
    QScrollArea* scrollContacts;
};

#endif // CONTACTSWIDGET_H
