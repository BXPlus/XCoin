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
#include "paycontactdialog.h"

namespace Ui {
class ContactsWidget;
}

class ContactsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContactsWidget(QWidget *parent = nullptr);
private:
    QLabel* title;
    QVBoxLayout* pageLayout;
    QGridLayout* contactGrid;
    QWidget* boxContainer;
    QScrollArea* scrollContacts;

    QPushButton* addContactButton;
    CustomButton* editBtn;

    QWidget* topBox;
    QHBoxLayout* topLayout;

    QMap<QString, QString> contactDict = {};
    QList<QPushButton*> delList;
    QList<QList<QString>> dictList = {{"Cyrus", "043A967EA681DE73DB77AFDB0AB6FDDA81D8974062D9D6A2D549FE75E558E306B6E26002963C39CB769DDFC43DE323C9624EAA74F167BF0F238BE62E708BE3BBA4"}, {"Bob", "#dk9174hdn29s"}, {"Alex", "048C91F222BDA13AFDE9CE5FE89E5677F629137EA2F5CF87EC2C0A8ABB08E42A08E7AD39FE593987A9F6E661F2F530D42BCBE0904CB17731EB55969BD9599D345B"},
                                      {"Youssef", "#dk9174hdn29s"}, {"Clara", "#dk9174hdn29s"}, {"Arthur", "#dk9174hdn29s"},
                                      {"Timothé", "#dk9174hdn29s"}, {"Tim", "#dk9174hdn29s"}, {"Jean Seb", "#dk9174hdn29s"}};
    QList<QLabel*> labelList;
    QString elDelete;

    void editContact();

    int editCount = 0;

    QLineEdit* contactSearch;
    void createDictionary(QMap<QString, QString>);
    void deleteWidgets();

private slots:
    void addContact();
    void deleteContact(int count);
    void editStyle();
    void contactSearchEdit();
    void openPayDialog(QString value);
    void dict();
};

#endif // CONTACTSWIDGET_H
