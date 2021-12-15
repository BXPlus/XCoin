#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QDialog>
#include <QMap>
#include "custombutton.h"
#include <QLineEdit>
#include <paycontactdialog.h>

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
    CustomButton* editBtn;

    QWidget* topBox;
    QHBoxLayout* topLayout;

    QMap<QString, QString> contactDict;
    QList<QPushButton*> delList;
    QString elDelete;

    void editContact();

    int editCount = 0;

    QLineEdit* contactSearch;
    void createDictionary(QMap<QString, QString>);
    //void deleteContact(int);
    void deleteWidgets();

private slots:
    void addContact();
    void deleteContact(int count);
    void editStyle();
    void get_key(QString key);
    void contactSearchEdit();
    void openPayDialog(QString value);
};

#endif // CONTACTSWIDGET_H
