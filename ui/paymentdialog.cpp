#include "paymentdialog.h"
#include <QDialog>
#include <QGroupBox>
#include <QList>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

PaymentDialog::PaymentDialog(QDialog *parent) :
    QDialog(parent)
{
//to activate the pay btn
    //    QPushButton* pay_btn = new QPushButton(QString("PAY NOW"), mainWidget);
    //        pay_btn->setMinimumSize(100,100);
    //        pay_btn->setStyleSheet("border-radius: 10px;"
    //                               "background-color: green;");
    //        connect(pay_btn, &QPushButton::released, this, &MainWindow::on_pushButton_clicked);

//    void MainWindow::on_pushButton_clicked()
//    {
//        PaymentDialog payment_window;
//        payment_window.setModal(true);
//        payment_window.exec();
//    }


    //set up layout linked to the widget of the whole page
QVBoxLayout* page_layout = new QVBoxLayout(this);
setLayout(page_layout);

    //Title of the Payments Page
    title_page_label = new QLabel(this);
    page_layout->addWidget(title_page_label);
    title_page_label->setMaximumHeight(45);

        title_page_label->setObjectName("title_page_label");
        title_page_label->setText(QString("PAY TO SOMEBODY"));
        title_page_label->setAlignment(Qt::AlignCenter);
    // End of the title

    // Box for payment

    pay_box = new QWidget(this);
    page_layout->addWidget(pay_box);
    pay_layout = new QVBoxLayout(pay_box);

        // First box to decide to whom send money
        QGroupBox* pay_someone_box = new QGroupBox(pay_box);
        QHBoxLayout* pay_someone_layout = new QHBoxLayout(pay_someone_box);
        pay_someone_box->setLayout(pay_someone_layout);
        pay_someone_box->setTitle("Pay to :");
        pay_layout->addWidget(pay_someone_box);
        pay_someone_box->setMaximumHeight(100);


            //Choose the money receiver
            QComboBox* friends = new QComboBox(pay_someone_box);
            pay_someone_layout->addWidget(friends);
                //list of my friends
                QStringList my_friends_list;
                QString my_friends = "God,Artur,Klara,Alexender,Timothée";
                my_friends_list = my_friends.split(",");
                friends->addItems(my_friends_list);

            //Second box to choose the amount to pay
                QGroupBox* amount_box = new QGroupBox(pay_box);
                QHBoxLayout* amount_layout = new QHBoxLayout(amount_box);
                amount_box->setLayout(amount_layout);
                amount_box->setTitle("Amount:");
                pay_layout->addWidget(amount_box);
                // Set boxes in order to choose the currency i.e. € or XCOIN
                QPushButton* XCO = new QPushButton(amount_box);
                amount_layout->addWidget(XCO);
                    XCO->setText(QString("XCO"));
                    XCO->setMaximumHeight(50);
                    XCO->setStyleSheet("border-radius: 10px;"
                                       "padding: 10px;"
                                       "background-color: yellow");


                // Set line to be filled with the amount desired to pay
                QLineEdit* line_edit= new QLineEdit(amount_box);
                amount_layout->addWidget(line_edit);

        QPushButton* pay_btn = new QPushButton("PAY NOW", this);
        QHBoxLayout* pay_btn_layout = new QHBoxLayout(pay_btn);
            pay_btn->setMinimumSize(100,100);
            pay_btn->setStyleSheet("border-radius: 10px;"
                                   "background-color: rgb(255, 190, 80);"
                                   "text-align: center");


//                    connect(pay_btn, &QPushButton::released, this, &PaymentDialog::handlepay_btn);
        page_layout->addWidget(pay_btn);

}




PaymentDialog::~PaymentDialog()
{
    delete ui;
}
