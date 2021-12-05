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
    //scroll->setStyleSheet("background-color: grey");

    QWidget* transacContainer = new QWidget(scroll);
    QVBoxLayout* transacLayout = new QVBoxLayout(transacContainer);

    scroll->setWidget(transacContainer);

    transacContainer->resize(500,500);
    QWidget* box1 = new QWidget(transacContainer);
    QWidget* box2 = new QWidget(transacContainer);
    QWidget* box3 = new QWidget(transacContainer);
    QWidget* box4 = new QWidget(transacContainer);
    QWidget* box5 = new QWidget(transacContainer);
    QWidget* box6 = new QWidget(transacContainer);


    //Names and Money Transaction in Boxes
    //

    //Layout for each box
    QVBoxLayout* box1layout = new QVBoxLayout(box1);
    QVBoxLayout* box2layout = new QVBoxLayout(box2);
    QVBoxLayout* box3layout = new QVBoxLayout(box3);
    QVBoxLayout* box4layout = new QVBoxLayout(box4);
    QVBoxLayout* box5layout = new QVBoxLayout(box5);
    QVBoxLayout* box6layout = new QVBoxLayout(box6);

    //Names and Money of each transaction
    QLabel* namebox1 = new QLabel(box1);
    QLabel* namebox2 = new QLabel(box2);
    QLabel* namebox3 = new QLabel(box3);
    QLabel* namebox4 = new QLabel(box4);
    QLabel* namebox5 = new QLabel(box5);
    QLabel* namebox6 = new QLabel(box6);

    QLabel* moneybox1 = new QLabel(box1);
    QLabel* moneybox2 = new QLabel(box2);
    QLabel* moneybox3 = new QLabel(box3);
    QLabel* moneybox4 = new QLabel(box4);
    QLabel* moneybox5 = new QLabel(box5);
    QLabel* moneybox6 = new QLabel(box6);


    QStringList names = {"Thomas", "Jean-Seb", "Marius", "Tim", "Youssef", "Clara"};
    QStringList money = {"-3.2 XCoin", "0.4 XCoin", "2 XCoin", "-0.2 XCoin", "0.3 XCoin", "1 XCoin"};
    QList<QWidget*> boxes = {box1, box2, box3, box4, box5, box6};
    QList<QLabel*> nameboxes  = {namebox1, namebox2, namebox3, namebox4, namebox5, namebox6};
    QList<QLabel*> moneyboxes  = {moneybox1, moneybox2, moneybox3, moneybox4, moneybox5, moneybox6};
    QList<QVBoxLayout*> layoutboxes = {box1layout, box2layout, box3layout, box4layout, box5layout, box6layout};

    for (int i=0; i<6; i++){
        layoutboxes[i]->addWidget(nameboxes[i]);
        nameboxes[i]->setObjectName(names[i]);
        nameboxes[i]->setText(QString(names[i]));
        nameboxes[i]->setMinimumSize(400, 100);
        nameboxes[i]->setAlignment(Qt::AlignHCenter);

        layoutboxes[i]->addWidget(moneyboxes[i]);
        moneyboxes[i]->setObjectName(money[i]);
        moneyboxes[i]->setText(QString(money[i]));
        moneyboxes[i]->setMinimumSize(400, 45);
        moneyboxes[i]->setAlignment(Qt::AlignHCenter);

        //Choose the color of the border of the boxes
        boxes[i]->setStyleSheet("border : 2px solid grey");
        nameboxes[i]->setStyleSheet("border: grey");
        moneyboxes[i]->setStyleSheet("border: grey");
    }

    //End Names and Money in Boxes

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

}

BalanceWidget::~BalanceWidget()
{
    delete ui;
}
