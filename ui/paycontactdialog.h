#ifndef PAYCONTACTDIALOG_H
#define PAYCONTACTDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class payContactDialog : public QDialog
{

public:
    explicit payContactDialog(QString publicKey, QWidget *parent = nullptr);
    ~payContactDialog();
private slots:
    void closed();
    void pay();
private:
    QVBoxLayout* mainLayout;
    QGridLayout* numberInputLayout;
    QHBoxLayout* bottomButtonsLayout;
    QPushButton* confirmBtn;
    QPushButton* cancelBtn;
    QLineEdit* amountEnter;
    QString* toKey;
    QLabel* title;
};

#endif // PAYCONTACTDIALOG_H
