#ifndef PAYCONTACTDIALOG_H
#define PAYCONTACTDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSignalMapper>
#include "../XNode/node.h"


class payContactDialog : public QDialog
{

public:
    explicit payContactDialog(QString name, QString publicKey, QWidget *parent = nullptr);
    ~payContactDialog();

private:
    QVBoxLayout* mainLayout;
    QGridLayout* numberInputLayout;
    QHBoxLayout* bottomButtonsLayout;
    QPushButton* confirmBtn;
    QPushButton* cancelBtn;
    QLineEdit* amountEnter;
    QString* toName;
    QString* toKey;
    QLabel* title;
    QLabel* subtitle;
    QLabel* enterPriceText;
    QLabel* enterPayText;
    QLineEdit* enterPay;
    QList<QPushButton>* digitBtnList;

private slots:
    void closed();
    void pay();
    void inputDigit(int);
};

#endif // PAYCONTACTDIALOG_H
