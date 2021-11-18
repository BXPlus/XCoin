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
    privateLabel = new QLabel("Private Key:", this);
    privateText = new QLineEdit(this);

    mainLayout = new QVBoxLayout();
    usernameLayout = new QHBoxLayout();

    usernameLayout->addWidget(privateLabel);
    usernameLayout->addWidget(privateText);

    groupBox->setLayout(usernameLayout);
    groupBox->setFlat(true);
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(login);
    setLayout(mainLayout);

    connect(login, SIGNAL(clicked()), this, SLOT(check_credentials()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::get_identified()
{
    return identified;
}

void LoginDialog::check_credentials()
{
    QString privatekey = privateText->text();

    if (privatekey == "0123456") {
        qDebug() << "works!";
        identified = true;
        this->close();
    }
    else {
        identified = false;
    }
}
