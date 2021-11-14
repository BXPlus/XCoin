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
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool get_login();

private:
    Ui::Login *ui;
    QGroupBox *group_box;
    QVBoxLayout *m_layout;
    QHBoxLayout *username_layout;
    QHBoxLayout *password_layout;
    QVBoxLayout *main_layout;

    QWidget *label_widget;
    QWidget *text_widget;

    QLabel *label_username;
    QLabel *label_password;
    QLineEdit *text_username;
    QLineEdit *text_password;
    CustomButton *enter;

    bool login;
private slots:
    void check_credentials();
};

#endif // LOGIN_H
