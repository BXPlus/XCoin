#include "logindialog.h"
#include "mainwindow.h"
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    groupBox = new QGroupBox();
    login = new QPushButton("Login", this);
    privateLabel = new QLabel("Private Key:", this);
    privateText = new QLineEdit(this);
    warningLabel = new QLabel(this);

    mainLayout = new QVBoxLayout();
    usernameLayout = new QHBoxLayout();

    usernameLayout->addWidget(privateLabel);
    usernameLayout->addWidget(privateText);

    groupBox->setLayout(usernameLayout);
    groupBox->setFlat(true);
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(warningLabel);
    mainLayout->addWidget(login);
    setLayout(mainLayout);

    warningLabel->setVisible(false);

    connect(login, SIGNAL(clicked()), this, SLOT(check_credentials()));
}

LoginDialog::~LoginDialog()
{
}

bool LoginDialog::get_identified()
{
    return identified;
}

void LoginDialog::check_credentials()
{
    QString privatekey = privateText->text();
    QStringList attemps = {"three", "two", "one"};

    if (privatekey == "") {
        identified = true;
        this->close();
    }
    else {
        warningLabel->setVisible(true);
        warningLabel->setStyleSheet("color: red;"
                                    "margin: 0;");

        if (counter < 2) {
            warningLabel->setText(QString("[WARNING] Only %1 attempts left!").arg(attemps[counter]));
            counter ++;
        }

        else if (counter == 2) {
            warningLabel->setText(QString("[WARNING] Only %1 attempt left!").arg(attemps[counter]));
            counter ++;
        }

        else {
            warningLabel->setText(QString("[WARNING] No more attemps allowed!"));
            groupBox->setVisible(false);
            login->hide();
        }
    }
}
