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
        // End of the title

        //Main box
        main_box = new QWidget(this);
        page_layout->addWidget(main_box);
        main_layout = new QVBoxLayout(main_box);


            // Creation of a box where the user set the amount desired
            QGroupBox* amount_group = new QGroupBox(main_box);
            amount_group->setTitle("Amount");
            QHBoxLayout* amount_layout = new QHBoxLayout();
            amount_group->setLayout(amount_layout);

                // Set boxes in order to choose the currency i.e. € or XCOIN
                QPushButton* euro = new QPushButton(amount_group);
                    euro->setObjectName("euro");
                    euro->setText(QString("€"));
                    euro->setMaximumHeight(50);
                    euro->setStyleSheet("border-radius: 10px;"
                                       "padding: 10px;");
                QPushButton* XCO = new QPushButton(amount_group);
                    XCO->setObjectName("XCO");
                    XCO->setText(QString("XCO"));
                    XCO->setMaximumHeight(50);
                    XCO->setStyleSheet("border-radius: 10px;"
                                       "padding: 10px;");


                // Set line to be filled with the amount desired to pay
                QLineEdit* line_edit= new QLineEdit(amount_group);

                //Set a Pay button that do an action once it's clicked
                //(thanks to the handlepay_btn function)
                pay_btn = new QPushButton(QString("PAY NOW"), amount_group);
                    pay_btn->setMinimumSize(100,100);

                    pay_btn->setStyleSheet("border-radius: 10px;"
                                           "background-color: green;");
//                    connect(pay_btn, &QPushButton::released, this, &PaymentDialog::handlepay_btn);

                // add the previous boxes and line to the layout
                amount_layout->addWidget(euro);
                amount_layout->addWidget(XCO);
                amount_layout->addWidget(line_edit);
                amount_layout->addWidget(pay_btn);

                // Creation of a box where it recaps the user basket in euro and in XCoin
                QGroupBox* total_group = new QGroupBox(main_box);
                total_group->setTitle("Total");
                QHBoxLayout* total_layout = new QHBoxLayout();
                total_group->setLayout(total_layout);

                    QPushButton* euro2 = new QPushButton(amount_group);
                        euro2->setObjectName("euro");
                        euro2->setText(QString("€"));
                        euro2->setMaximumHeight(50);
                        euro2->setStyleSheet("border-radius: 10px;"
                                           "padding: 10px;");
                    XCO2 = new QPushButton(amount_group);
                        XCO2->setObjectName("XCO");
                        XCO2->setText(QString("XCO"));
                        XCO2->setMaximumHeight(50);
                        XCO2->setStyleSheet("border-radius: 10px;"
                                           "padding: 10px;");

                    // Set line to be filled with the amount desired to pay
                    QLineEdit* line_edit2= new QLineEdit(amount_group);
                    QLineEdit* line_edit3= new QLineEdit(amount_group);

                    //Set a Pay button that do an action once it's clicked
                    //(thanks to the handle button function)
                    pay_btn = new QPushButton(QString("PAY NOW"), main_box);
                        pay_btn->setMinimumSize(100,100);
                        pay_btn->setStyleSheet("border-radius: 10px;"
                                               "background-color: green;");
//                        connect(pay_btn, &QPushButton::released, this, &PaymentDialog::handlepay_btn);

                total_layout->addWidget(euro2);
                total_layout->addWidget(line_edit2);
                total_layout->addWidget(XCO2);
                total_layout->addWidget(line_edit3);

            main_layout->addWidget(amount_group);
            main_layout->addWidget(total_group);
            main_layout->addWidget(pay_btn);





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
