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
    bool get_identified();

private:
    Ui::LoginDialog *ui;
    QGroupBox *groupBox;
    QHBoxLayout *usernameLayout;
    QVBoxLayout *mainLayout;

    QWidget *labelWidget;
    QWidget *textWidget;

    QLabel *privateLabel;
    QLineEdit *privateText;
    QPushButton *login;

    bool identified;
private slots:
    void check_credentials();
};

#endif // LOGIN_H
