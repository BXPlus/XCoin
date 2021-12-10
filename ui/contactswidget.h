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
    CustomButton* editBtn;

    QWidget* topBox;
    QHBoxLayout* topLayout;

    QMap<QString, QString> contactDict;
    QList<CustomButton*> delList;
    QString elDelete;

    void create_dictionnary();
    void delete_widgets();
    void edit_contact();

    int editCount = 0;
private slots:
    void addContact();
    void deleteContact(int count);
    void editStyle();
    void get_key(QString key);
};

#endif // CONTACTSWIDGET_H
