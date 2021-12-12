#include "paycontactdialog.h"
#include <QDebug>

payContactDialog::payContactDialog(QString publicKey, QWidget* parent) :
    QDialog(parent)
{
    toKey = new QString(publicKey);
    setWindowTitle("Pay");
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    title = new QLabel(this);
    title->setText(QString("Paying " + *toKey));
    title->setStyleSheet("color: black;");

    amountEnter = new QLineEdit(this);

    numberInputLayout = new QGridLayout();
    QPushButton* zeroBtn = new QPushButton("0", this);
    numberInputLayout->addWidget(zeroBtn, 3, 1);
    for (int i=1; i<10; i++) {
        QPushButton* nbBtn = new QPushButton(QString::number(i), this);
        int y;
        if (i%3-1 == -1){y = 2;}
        else{y = i%3-1;}
        numberInputLayout->addWidget(nbBtn, 2-int(i*0.33), y);
    }


    confirmBtn = new QPushButton("Confirm", this);
    confirmBtn->setObjectName("confirmPaymentButton");
    confirmBtn->setStyleSheet("background-color: green;");
    cancelBtn = new QPushButton("Cancel", this);
    cancelBtn->setObjectName("cancelPaymentButton");
    cancelBtn->setStyleSheet("background-color: red;");
    bottomButtonsLayout = new QHBoxLayout();
    bottomButtonsLayout->addWidget(cancelBtn);
    bottomButtonsLayout->addWidget(confirmBtn);

    connect(cancelBtn,  &QPushButton::clicked, this, &payContactDialog::close);
    connect(confirmBtn, &QPushButton::clicked, this, &payContactDialog::pay);

    mainLayout->addWidget(title);
    mainLayout->addWidget(amountEnter);
    mainLayout->addLayout(numberInputLayout);
    mainLayout->addLayout(bottomButtonsLayout);
}
payContactDialog::~payContactDialog(){

}

void payContactDialog::closed()
{
    this->close();
}

void payContactDialog::pay(){
    qDebug() << "Paying " << amountEnter->text().toInt() << "XCoins" << "to" << *toKey;
    this->close();
}
