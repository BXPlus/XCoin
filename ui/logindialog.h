#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <mainwindow.h>
#include <custombutton.h>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    bool get_login();

private:
    Ui::LoginDialog *ui;
    QGroupBox *groupBox;
    QVBoxLayout *mLayout;
    QHBoxLayout *usernameLayout;
    QHBoxLayout *passwordLayout;
    QVBoxLayout *mainLayout;

    QWidget *labelWidget;
    QWidget *textWidget;

    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *usernameText;
    QLineEdit *passwordText;
    QPushButton *login;

    bool identified;
private slots:
    void check_credentials();
};

#endif // LOGIN_H
