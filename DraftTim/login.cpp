#include "login.h"
#include "ui_login.h"
#include "login.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    group_box = new QGroupBox(tr("Login"));
    enter = new CustomButton("Login", this);
    label_username = new QLabel("Username:", this);
    label_password = new QLabel("Password:", this);
    text_username = new QLineEdit(this);
    text_password = new QLineEdit(this);

    main_layout = new QVBoxLayout();
    username_layout = new QHBoxLayout();
    password_layout = new QHBoxLayout();
    m_layout = new QVBoxLayout();

    password_layout->addWidget(label_password);
    username_layout->addWidget(label_username);
    password_layout->addWidget(text_password);
    username_layout->addWidget(text_username);

    m_layout->addLayout(username_layout);
    m_layout->addLayout(password_layout);

    group_box->setLayout(m_layout);
    group_box->setFlat(true);
    main_layout->addWidget(group_box);
    main_layout->addWidget(enter);
    setLayout(main_layout);
}

Login::~Login()
{
    delete ui;
}

bool Login::get_login()
{
    return login;
}

void Login::check_credentials()
{
    QString username = text_username->text();
    QString password = text_password->text();

    if (username == "tim_vlc" && password == "Tim") {
        login = true;
    }
    login = false;
}
