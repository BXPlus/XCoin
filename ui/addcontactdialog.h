#ifndef ADDCONTACTDIALOG_H
#define ADDCONTACTDIALOG_H

#include <QDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class addContactDialog;
}

class addContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addContactDialog(QWidget *parent = nullptr);
    ~addContactDialog();
    QList<QString> get_info();
    bool click = false;
    bool get_click();
private slots:
    void closed();
private:
    QVBoxLayout* mainLayout;
    QPushButton* addBtn;

    QList<QString> sList;
    QList<QLabel*> labelList;
    QList<QLineEdit*> lineList;
    QList<QVBoxLayout*> layoutList;
};

#endif // ADDCONTACTDIALOG_H
