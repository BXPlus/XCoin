#include "logindialog.h"
#include "ui_logindialog.h"
#include "logindialog.h"
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    groupBox = new QGroupBox(tr("Login"));
    login = new QPushButton("Login", this);
    usernameLabel = new QLabel("Username:", this);
    passwordLabel = new QLabel("Password:", this);
    usernameText = new QLineEdit(this);
    passwordText = new QLineEdit(this);

    mainLayout = new QVBoxLayout();
    usernameLayout = new QHBoxLayout();
    passwordLayout = new QHBoxLayout();
    mLayout = new QVBoxLayout();

    passwordLayout->addWidget(passwordLabel );
    usernameLayout->addWidget(usernameLabel);
    passwordLayout->addWidget(passwordText);
    usernameLayout->addWidget(usernameText);

    mLayout->addLayout(usernameLayout);
    mLayout->addLayout(passwordLayout);

    groupBox->setLayout(mLayout);
    groupBox->setFlat(true);
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(login);
    setLayout(mainLayout);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::get_login()
{
    return login;
}

void LoginDialog::check_credentials()
{
    QString username = usernameText->text();
    QString password = passwordText->text();

    if (username == "tim_vlc" && password == "Tim") {
        identified = true;
    }
    identified = false;
}
