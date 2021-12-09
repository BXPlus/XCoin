#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QDialog>
#include <QMap>

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
    QPushButton* addContactButton;
    QWidget* topBox;
    QHBoxLayout* topLayout;
    QDialog* addContactDialog;
};

#endif // CONTACTSWIDGET_H
