#include "balancewidget2.h"
#include "mainwindow.h"

BalanceWidget2::BalanceWidget2(QWidget *parent) : QWidget(parent)
{
    tabWidget = new QTabWidget(this);
    mainLayout = new QVBoxLayout();

    //Setup main tabs
    titleList = {"Bank Statement", "To Come", "Spending", "Income"};

    for (int i = 0; i < 4; i++) {
        QWidget* tab = new QWidget(this);
        tabList.append(tab);

        QVBoxLayout* layout = new QVBoxLayout();
        layoutList.append(layout);

        tab->setLayout(layout);
        tabWidget->addTab(tab, titleList[i]);
    }

    //Create Balance Widget
    balanceList = {"Balance as of 12/10/2021:", "941.3 XCoin", "To come: -23.4 XCoin"
                , "Forecast: 917.9 XCoin"};
    bWidget = new QWidget(this);
    balanceLayout = new QHBoxLayout();
    bWidget->setLayout(balanceLayout);
    bWidget->setObjectName("BalanceWidget");

    QVBoxLayout* smallLayout = new QVBoxLayout();
    QVBoxLayout* bigLayout = new QVBoxLayout();

    for (int i = 0; i < 4; i++) {
        QLabel* label = new QLabel(balanceList[i], this);
        labelList.append(label);
        if (i != 1) {
            label->setMaximumSize(200, 12);
        }
        else {
            label->setMaximumSize(200, 55);
        }

        if (i <= 1) {
            bigLayout->addWidget(label, 50, Qt::AlignCenter);
        }

        else {
            smallLayout->addWidget(label, 50, Qt::AlignCenter);
        }
    }
    labelList[1]->setObjectName("BalanceAmount");

    balanceLayout->addLayout(bigLayout);
    balanceLayout->addLayout(smallLayout);
    bWidget->setMaximumSize(600, 100);
    layoutList[0]->addWidget(bWidget, 20, Qt::AlignTop);

    //Setup of balance history scroll area
    typeList = {"Reimbursement from Tim", "Restaurant", "Hotel", "Commision",
               "Lydia", "Bar", "SuperMarket", "Transaction Alex",
               "Superette", "Boulangerie", "Wine Cellar", "CarWash",
               "Online payment Nike", "Ikea Furniture"};
    amountList = {"+ 20 XCoin", "-64.5 XCoin", "- 230 XCoin", "- 7.1 XCoin",
                 "+ 36 XCoin", "- 12 XCoin", "- 189 XCoin", "+ 90 XCoin",
                 "- 22.7 XCoin", "- 1.23 XCoin", "- 15 XCoin", "- 6 XCoin",
                 "- 127 XCoin", "- 390 XCoin"};

    for (int i = 0; i < typeList.length(); i++) {
        balanceDict[typeList[i]] = amountList[i];
    }

    scrollBalance = new QScrollArea(this);
    boxContainer = new QWidget(scrollBalance);
    scrollBalance->setWidget(boxContainer);
    scrollBalance->setWidgetResizable(true);
    boxContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    balanceGrid = new QGridLayout(boxContainer);
    balanceGrid->setContentsMargins(0, 0, 0, 0);
    balanceGrid->setSpacing(0);

    for(auto e : balanceDict.keys())
    {
        QLabel* key = new QLabel;
        key->setText(e);
        QLabel* value = new QLabel;
        value->setText(balanceDict.value(e));
        key->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        value->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        int count = balanceGrid->rowCount();
        if (count%2 == 1){
            key->setStyleSheet("background-color: rgba(60, 72, 114, 255);"
                               "padding: 20;"
                               "font: 15px;"
                               "border-top-left-radius: 5px;"
                               "border-bottom-left-radius: 5px;");
            value->setStyleSheet("background-color: rgba(60, 72, 114, 255);"
                                 "padding: 20;"
                                 "font: bold 15px;");
        }
        else{
            key->setStyleSheet("background-color: rgba(31,41,66,255);"
                               "padding: 20;"
                               "font: 15px;"
                               "border-top-left-radius: 5px;"
                               "border-bottom-left-radius: 5px;");
            value->setStyleSheet("background-color: rgba(31,41,66,255);"
                                 "padding: 20;"
                                 "font: bold 15px;");
        }
        balanceGrid->addWidget(key, count, 0);
        balanceGrid->addWidget(value, count, 1);
    }

    layoutList[0]->addWidget(scrollBalance);
    //Set main layouts
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
