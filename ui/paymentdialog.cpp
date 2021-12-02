#include "paymentdialog.h"
#include "ui_paymentdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QSizePolicy>
#include <QStaticText>
#include <QGroupBox>
#include <QTextEdit>
#include <QLineEdit>
#include <custombutton.h>
#include <QAction>
#include <QBoxLayout>

PaymentDialog::PaymentDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaymentDialog)
{
    ui->setupUi(this);

        //set up layout linked to the widget of the whole page
    QVBoxLayout* page_layout = new QVBoxLayout(this);
    setLayout(page_layout);



        //Title of the Payments Page
        title_page_label = new QLabel(this);
        page_layout->addWidget(title_page_label);
        title_page_label->setMaximumHeight(45);

            title_page_label->setObjectName("title_page_label");
            title_page_label->setText(QString("Purchase XCoin"));
            title_page_label->setAlignment(Qt::AlignCenter);



        purchasing_box = new QWidget(this);
        page_layout->addWidget(purchasing_box);
        purchasing_layout = new QVBoxLayout(purchasing_box);



            QGroupBox* amount_group = new QGroupBox(purchasing_box);
            amount_group->setTitle("Amount");

            QHBoxLayout* amount_layout = new QHBoxLayout();
            amount_group->setLayout(amount_layout);
                // Set boxes in order to choose the currency i.e. € or XCOIN
                QLabel* euro = new QLabel(amount_group);
                    euro->setObjectName("euro");
                    euro->setText(QString("€"));
                    euro->setMaximumSize(30,30);
                    euro->setAlignment(Qt::AlignTop);
                QLabel* XCO = new QLabel(amount_group);
                    XCO->setObjectName("XCO");
                    XCO->setText(QString("XCO"));
                    XCO->setMaximumSize(40,30);
                    XCO->setAlignment(Qt::AlignTop);
                // Set line to be filled with the amount desired to pay
                QLineEdit* line_edit= new QLineEdit(amount_group);
                //Set a Pay button that do an action once it's clicked
                //(thanks to the handle button function)
                pay_btn = new QPushButton(QString("PAY"), amount_group);
    //example of setgeo pay_btn->setGeometry(QRect(QPoint(100, 100), QSize(100, 100)));
                    pay_btn->setMinimumSize(100,100);
                    pay_btn->setStyleSheet("border-radius: 10px;"
                                           "background-color: yellow;");
                    connect(pay_btn, &QPushButton::released, this, &PaymentDialog::handlepay_btn);

                amount_layout->addWidget(euro);
                amount_layout->addWidget(XCO);
                amount_layout->addWidget(line_edit);
                amount_layout->addWidget(pay_btn);

                QGroupBox* total_group = new QGroupBox(purchasing_box);
                total_group->setTitle("Total");

                QHBoxLayout* total_layout = new QHBoxLayout();
                total_group->setLayout(total_layout);

    //                    //Set a Pay button that do an action once it's clicked
    //                    //(thanks to the handle button function)
    //                    pay_btn = new QPushButton(QString("PAY"), purchasing_box);
    //    //example of setgeo pay_btn->setGeometry(QRect(QPoint(100, 100), QSize(100, 100)));
    //                        pay_btn->setMinimumSize(100,100);
    //                        pay_btn->setStyleSheet("border-radius: 10px;"
    //                                               "background-color: yellow;");
    //                        connect(pay_btn, &QPushButton::released, this, &Payments::handlepay_btn);

                total_layout->addWidget(euro);
                total_layout->addWidget(line_edit);
                total_layout->addWidget(XCO);
                total_layout->addWidget(line_edit);

            purchasing_layout->addWidget(amount_group);
            purchasing_layout->addWidget(total_group);
            purchasing_layout->addWidget(pay_btn);





}

void PaymentDialog::handlepay_btn() {
  // change the text
  pay_btn->setText("Are you sure ?");
  pay_btn->setStyleSheet("background-color:red;");
  pay_btn->setMinimumSize(120,30);
  // example resize button
//      pay_btn->resize(110,30);
}


PaymentDialog::~PaymentDialog()
{
    delete ui;
}
