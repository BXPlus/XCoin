#include "paycontactdialog.h"
#include <QDebug>
#include <QAction>
#include "balancewidget.h"

payContactDialog::payContactDialog(QString publicKey, QWidget* parent) :
    QDialog(parent)
{
    this->setFixedSize(300, 300);
    this->setStyleSheet("background-color: white;");
    toKey = new QString(publicKey);
    setWindowTitle("Pay");
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    title = new QLabel(this);
    title->setText(QString("Paying " + *toKey));
    title->setObjectName("payContactDialogTitle");

    enterPayText = new QLabel(this);
    enterPayText->setText(QString("Payment Object:"));
    enterPayText->setStyleSheet("font-size: 15px;"
                                "color: black;");

    enterPay = new QLineEdit(this);
    enterPay->setPlaceholderText(QString("Object..."));
    enterPay->setStyleSheet("color: black;"
                            "border: 1px solid gray;"
                            "border-radius: 4px;"
                            "padding: 5px;");

    enterPriceText = new QLabel(this);
    enterPriceText->setText(QString("Wire Amount (XCoins)"));
    enterPriceText->setStyleSheet("font-size: 15px;"
                                  "color: black;");

    amountEnter = new QLineEdit(this);
    amountEnter->setStyleSheet("color: black;"
                               "border: 1px solid gray;"
                               "border-radius: 4px;"
                               "padding: 5px;"
                               "margin-bottom: 5px;");

//    numberInputLayout = new QGridLayout();
//    QPushButton* zeroBtn = new QPushButton("0", this);
//    digitBtnList->append(zeroBtn);
//    numberInputLayout->addWidget(zeroBtn, 3, 1);
//    for (int i=1; i<10; i++) {
//        QPushButton* nbBtn = new QPushButton(QString::number(i), this);
//        int y;
//        if (i%3-1 == -1){y = 2;}
//        else{y = i%3-1;}

        // Button connect doesn't work: delete at the end if doesn't work
        //QSignalMapper* signalMapper = new QSignalMapper(this);
        //connect(nbBtn, SIGNAL(clicked()), signalMapper, SLOT(map()));
        //signalMapper->setMapping(nbBtn, i);
        //connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(inputDigit(int)));

//        numberInputLayout->addWidget(nbBtn, 2-int(i*0.33), y);
//    }

    confirmBtn = new QPushButton("Confirm", this);
    confirmBtn->setObjectName("confirmPaymentButton");
    confirmBtn->setStyleSheet("background-color: green;"
                                        "border-radius: 4px;"
                                        "padding: 5px;");
    cancelBtn = new QPushButton("Cancel", this);
    cancelBtn->setObjectName("cancelPaymentButton");
    cancelBtn->setStyleSheet("background-color: red;"
                                       "border-radius: 4px;"
                                       "padding: 5px;");
    bottomButtonsLayout = new QHBoxLayout();
    bottomButtonsLayout->addWidget(cancelBtn);
    bottomButtonsLayout->addWidget(confirmBtn);

    connect(cancelBtn,  &QPushButton::clicked, this, &payContactDialog::close);
    connect(confirmBtn, &QPushButton::clicked, this, &payContactDialog::pay);

    mainLayout->addWidget(title);
    mainLayout->addWidget(enterPayText);
    mainLayout->addWidget(enterPay);
    mainLayout->addWidget(enterPriceText);
    mainLayout->addWidget(amountEnter);
    mainLayout->addLayout(bottomButtonsLayout);
}

payContactDialog::~payContactDialog(){
}

void payContactDialog::closed(){
    this->close();
}

void payContactDialog::pay(){
    qDebug() << "Paying" << amountEnter->text().toInt() << "XCoins" << "to" << *toKey << "for" << enterPay->text();
    parentWidget()->parentWidget()->parentWidget()->findChild<BalanceWidget*>("BalanceWidget")->editBalanceDict(enterPay->text(), amountEnter->text());
    this->close();
}

void payContactDialog::inputDigit(int i){
    amountEnter->setText(amountEnter->text() + QString::number(i));
}








