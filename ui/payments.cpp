#include "payments.h"
#include "ui_payments.h"
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QSizePolicy>
#include <QStaticText>

Payments::Payments(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Payments)
{
    ui->setupUi(this);
    //QWidget* page_container = new QWidget(this);
    QVBoxLayout* page_layout = new QVBoxLayout(this);
    //page_container-> setMinimumSize(500,600);
    //page_container->resize(400,600);


        //Title of the Payments Page
        QLabel* title_page_label = new QLabel(this);
        page_layout->addWidget(title_page_label);
        title_page_label->setObjectName("title_page_label");
        title_page_label->setText(QString("Purchase XCoin"));
        title_page_label->setMinimumSize(400,45);
        title_page_label->setAlignment(Qt::AlignHCenter);



        QWidget* purchasing_box = new QWidget(this);
        page_layout->addWidget(purchasing_box);
        QVBoxLayout* purchasing_layout = new QVBoxLayout(purchasing_box);

            QLabel* amount_title = new QLabel(purchasing_box);
            purchasing_layout->addWidget(amount_title);
                amount_title->setText(QString("Amount:"));
                amount_title->setAlignment(Qt::AlignTop);
                amount_title->move(0,250);

    setLayout(page_layout);

            //QWidget* money_value_box = new QWidget(purchasing_box);
            //QHBoxLayout* money_value_layout = new QHBoxLayout(money_value_box);

                /*QWidget* currency = new QWidget(money_value_box);
                money_value_layout->addWidget(currency);
                QHBoxLayout* currency_layout = new QHBoxLayout(currency);
                    QLabel* euro = new QLabel(currency);
                    QLabel* xco = new QLabel(currency);
                        currency_layout->addWidget(euro);
                        currency_layout->addWidget(xco);
                        euro->setText(QString("€"));
                        xco->setText(QString("XCO"));

                QWidget* fill_value = new QWidget(money_value_box);
                fill_value->setMinimumWidth(200);
*/










    //page_layout->addWidget(purchasing_box);






}

Payments::~Payments()
{
    delete ui;
}
