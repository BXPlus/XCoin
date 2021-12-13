#ifndef PAYCONTACTDIALOG_H
#define PAYCONTACTDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSignalMapper>

class payContactDialog : public QDialog
{

public:
    explicit payContactDialog(QString publicKey, QWidget *parent = nullptr);
    ~payContactDialog();
private:
    QVBoxLayout* mainLayout;
    QGridLayout* numberInputLayout;
    QHBoxLayout* bottomButtonsLayout;
    QPushButton* confirmBtn;
    QPushButton* cancelBtn;
    QLineEdit* amountEnter;
    QString* toKey;
    QLabel* title;
    QList<QPushButton>* digitBtnList;
private slots:
    void closed();
    void pay();
    void inputDigit(int);
};

#endif // PAYCONTACTDIALOG_H
