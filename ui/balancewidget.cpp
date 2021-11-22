#include "balancewidget.h"
#include "ui_balancewidget.h"
#include <custombutton.h>
#include <QBoxLayout>

BalanceWidget::BalanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BalanceWidget)
{
    ui->setupUi(this);
    setWindowTitle("balance");
    setMinimumSize(500,600);

    //Set the layout for the balance widget
    balanceWidget = new QWidget(this);
    hbalanceLayout = new QHBoxLayout(balanceWidget);

    //test
    //vbalanceLayout = new QVBoxLayout(balanceWidget);
    //CustomButton* test = new CustomButton("wsh", balanceWidget);
    //hbalanceLayout->addLayout(vbalanceLayout);
    //hbalanceLayout->addWidget(test);

    //Set the layout for the transactions
    transacContainer = new QWidget(balanceWidget);
    transacLayout = new QVBoxLayout(transacContainer);
    transacContainer->setLayout(hbalanceLayout);
    hbalanceLayout->addWidget(transacContainer);
    transacContainer->setMaximumWidth(200);
    transacLayout->addSpacing(10);


    //test
    //hbalanceLayout->addWidget(test);


    balanceWidget->setLayout(transacLayout);

    //test
    //balanceWidget->setLayout(hbalanceLayout);

    for (int i=0; i<6; i++){
        CustomButton* btn = new CustomButton("user i", transacContainer);
        btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        btn->setCursor(Qt::PointingHandCursor);
        transacLayout->addWidget(btn);
    }

    setLayout(transacLayout);
}

BalanceWidget::~BalanceWidget()
{
    delete ui;
}
