#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QDialog>
#include "mainwindow.h"

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
    QMap<QString, QString> contactDict;

    void create_dictionnary();
    void delete_widgets();
private slots:
    void addContact();
};

#endif // CONTACTSWIDGET_H
