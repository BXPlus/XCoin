#include "balancewidget.h"
#include "ui_balancewidget.h"
#include <custombutton.h>
#include <QBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QStaticText>
#include <QSize>
#include <QScrollArea>
#include <QScrollBar>
#include <QGraphicsWidget>


BalanceWidget::BalanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BalanceWidget)
{
    ui->setupUi(this);

    QVBoxLayout* vbalanceLayout = new QVBoxLayout(this);

    //Upper Box Name
    QLabel* labelbalance = new QLabel(this);
    vbalanceLayout->addWidget(labelbalance);
    labelbalance->setObjectName("labelbalance");
    labelbalance->setText(QString("Your Current Balance is : "));
    labelbalance->setMinimumSize(400, 45);
    labelbalance->setAlignment(Qt::AlignHCenter);

    //Lower Box Name
    QLabel* latest_transac_title = new QLabel(this);
    vbalanceLayout->addWidget(latest_transac_title);
    latest_transac_title->setObjectName("latesttransac");
    latest_transac_title->setText(QString("History of Transactions : "));
    latest_transac_title->setMinimumSize(400, 45);
    latest_transac_title->setAlignment(Qt::AlignHCenter);

    //Scroll Bar

    QWidget* scrollWidget = new QWidget(this);
    QScrollArea* scroll = new QScrollArea (scrollWidget) ;
    QBoxLayout* boxWidgetLayout = new QBoxLayout(QBoxLayout::TopToBottom, scrollWidget) ;

    //Remove horizontal scrollbar
    scroll->horizontalScrollBar()->setEnabled(false);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    boxWidgetLayout->addWidget(scroll);
    boxWidgetLayout->setAlignment(scroll,Qt::AlignHCenter);

    QWidget* transacContainer = new QWidget(scroll);
    QVBoxLayout* transacLayout = new QVBoxLayout(transacContainer);

    scroll->setWidget(transacContainer);

    transacContainer->resize(1000,500);
    QWidget* box1 = new QWidget(transacContainer);
    QWidget* box2 = new QWidget(transacContainer);
    QWidget* box3 = new QWidget(transacContainer);
    QWidget* box4 = new QWidget(transacContainer);
    QWidget* box5 = new QWidget(transacContainer);
    QWidget* box6 = new QWidget(transacContainer);

    box1->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    box2->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    box3->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    box4->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    box5->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    box6->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);


    transacLayout->addWidget(box1);
    transacLayout->addWidget(box2);
    transacLayout->addWidget(box3);
    transacLayout->addWidget(box4);
    transacLayout->addWidget(box5);
    transacLayout->addWidget(box6);


    vbalanceLayout->addWidget(scrollWidget);



    //setWindowTitle("balance");
    //setMinimumSize(500,600);

    //Set the layout for the balance widget
    //balanceWidget = new QWidget(this);
    //hbalanceLayout = new QHBoxLayout(balanceWidget);



    //Set the layout for the transactions
    //transacContainer = new QWidget(balanceWidget);
    //transacLayout = new QVBoxLayout(transacContainer);
    //hbalanceLayout->addWidget(transacContainer);
    //transacContainer->setMaximumWidth(200);
    //transacLayout->addSpacing(10)

    //balanceWidget->setLayout(transacLayout);


    //for (int i=0; i<6; i++){
      //  QLabel *label = new QLabel(transacContainer);
      //  label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
      //  label->setText("first");
      //  label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
      //  transacLayout->addWidget(label);
    //}

    //setLayout(transacLayout);
}

BalanceWidget::~BalanceWidget()
{
    delete ui;
}
