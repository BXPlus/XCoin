#include "purchase_xcoin.h"
#include "ui_purchase_xcoin.h"
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

Purchase_XCoin::Purchase_XCoin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Purchase_XCoin)
{
    ui->setupUi(this);

    //set up layout linked to the widget of the whole page
QVBoxLayout* page_layout = new QVBoxLayout(this);
setLayout(page_layout);

    //Title of the Payments Page
//    title_page = new QWidget(this);
//    page_layout->addWidget(title_page);
//    title_page->setMaximumHeight(45);

        QLabel* purchase_title = new QLabel("Purchase XCoin",this);
            page_layout->addWidget(purchase_title);
            purchase_title->setObjectName("purchase_title");
            purchase_title->setAlignment(Qt::AlignCenter);
            purchase_title->setMaximumHeight(45);

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
                                   "padding: 10px;"
                                    "text-align: center");
            QPushButton* XCO = new QPushButton(amount_group);
                XCO->setObjectName("XCO");
                XCO->setText(QString("XCO"));
                XCO->setMaximumHeight(50);
                XCO->setStyleSheet("border-radius: 10px;"
                                   "padding: 10px;"
                                   "text-align: center");


            // Set line to be filled with the amount desired to pay
            QLineEdit* line_edit= new QLineEdit(amount_group);

            //Set a Pay button that do an action once it's clicked
            //(thanks to the handlepay_btn function)
            pay_btn = new QPushButton(QString("PAY NOW"), amount_group);
                pay_btn->setMinimumSize(100,100);

                pay_btn->setStyleSheet("border-radius: 10px;"
                                       "background-color: green;"
                                       "text-align:center");
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
                    euro2->setText(QString("€"));
                    euro2->setMaximumHeight(50);
                    euro2->setStyleSheet("border-radius: 10px;"
                                         "padding: 10px;"
                                         "background-color: rgba(0,150,255);"
                                         "text-align:center");
                XCO2 = new QPushButton(amount_group);
                    XCO2->setObjectName("XCO");
                    XCO2->setText(QString("XCO"));
                    XCO2->setMaximumHeight(50);
                    XCO2->setStyleSheet("border-radius: 10px;"
                                       "padding: 10px;"
                                       "background-color: yellow;"
                                       "text-align: center");


                // Set line to be filled with the amount desired to pay
                QLineEdit* line_edit2= new QLineEdit(amount_group);
                QLineEdit* line_edit3= new QLineEdit(amount_group);

                //Set a Pay button that do an action once it's clicked
                //(thanks to the handle button function)
                pay_btn = new QPushButton(QString("PAY NOW"), main_box);
                    pay_btn->setMinimumSize(100,100);

                    pay_btn->setStyleSheet("border-radius: 10px;"
                                           "background-color: green;"
                                           "text-align: center");

//                        connect(pay_btn, &QPushButton::released, this, &PaymentDialog::handlepay_btn);

            total_layout->addWidget(euro2);
            total_layout->addWidget(line_edit2);
            total_layout->addWidget(XCO2);
            total_layout->addWidget(line_edit3);

        main_layout->addWidget(amount_group);
        main_layout->addWidget(total_group);
        main_layout->addWidget(pay_btn);
}

Purchase_XCoin::~Purchase_XCoin()
{
    delete ui;
}
