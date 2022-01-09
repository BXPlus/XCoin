#include "balancewidget.h"
#include "mainwindow.h"
#include <qdebug.h>

BalanceWidget::BalanceWidget(QWidget *parent) : QWidget(parent)
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

    balanceList = {QString("Balance as of 12/10/2021:"), QString("To come: -23.4 XCoin")
                , QString("Forecast: 917.9 XCoin")};
    bWidget = new QWidget(this);
    balanceLayout = new QHBoxLayout();
    bWidget->setLayout(balanceLayout);
    bWidget->setObjectName("BalanceWidget");

    smallLayout = new QVBoxLayout();
    bigLayout = new QVBoxLayout();

    userBalance = ((MainWindow*)parentWidget()->parentWidget())->getUserBalance();
    userBalanceLabel = new QLabel(QString(QString::number(userBalance) + " XCoin"), this);

    labelList.append(userBalanceLabel);
    userBalanceLabel->setMaximumSize(200,55);
    userBalanceLabel->setObjectName("BalanceAmount");

    for (int i = 0; i < 3; i++) {
        QLabel* label = new QLabel(balanceList[i], this);
        labelList.append(label);
        label->setMaximumSize(200, 12);

        if (i == 0) {
            bigLayout->addWidget(label, 50, Qt::AlignCenter);
        }

        else {
            smallLayout->addWidget(label, 50, Qt::AlignCenter);
        }
    }

    bigLayout->addWidget(userBalanceLabel, 50, Qt::AlignCenter);

    balanceLayout->addLayout(bigLayout);
    balanceLayout->addLayout(smallLayout);
    bWidget->setMaximumSize(600, 100);
    layoutList[0]->addWidget(bWidget, 20, Qt::AlignTop);

    //Setup of balance history scroll area

    scrollBalance = new QScrollArea(this);
    boxContainer = new QWidget(scrollBalance);
    scrollBalance->setWidget(boxContainer);
    scrollBalance->setWidgetResizable(true);
    boxContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    balanceGrid = new QGridLayout(boxContainer);
    balanceGrid->setContentsMargins(0, 0, 0, 0);
    balanceGrid->setSpacing(0);
    boxContainer->setObjectName("ScrollBox");

    typeList = {"Reimbursement from Tim", "Restaurant", "Hotel", "Commission",
                "Lydia", "Bar", "SuperMarket", "Transaction Alex",
                "Superette", "Boulangerie", "Wine Cellar", "CarWash",
                "Online payment Nike"};
    typeList.append("Ikea Furniture");
    amountList = {"+ 20 XCoin", "-64.5 XCoin", "- 230 XCoin", "- 7.1 XCoin",
                  "+ 36 XCoin", "- 12 XCoin", "- 189 XCoin", "+ 90 XCoin",
                  "- 22.7 XCoin", "- 1.23 XCoin", "- 15 XCoin", "- 6 XCoin",
                  "- 127 XCoin", "- 390 XCoin"};
    createDictionary();

    layoutList[0]->addWidget(scrollBalance);
    //Set main layouts
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

void BalanceWidget::createDictionary(){

    for (int i = 0; i < typeList.length(); i++) {
        balanceDict[typeList[i]] = amountList[i];
    }

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
            key->setObjectName("keyBalance1");
            value->setObjectName("valueBalance1");
        }
        else{
            key->setObjectName("keyBalance2");
            value->setObjectName("valueBalance2");
        }

        balanceGrid->addWidget(key, count, 0);
        balanceGrid->addWidget(value, count, 1);
    }
    userBalanceLabel->setText(QString(QString::number(userBalance) + " XCoin"));
}

void BalanceWidget::editBalanceDict(QString object, QString amount) {
    // this function is a slot, signalled when payment done (only decreases userBalance)
    updateBalance(0, amount.toInt());
    ((MainWindow*)parentWidget()->parentWidget()->parentWidget())->editUserBalance(0, amount.toInt());

    deleteWidgets();
    typeList.append(object);
    amountList.append(QString("- "+amount+" XCoin"));
    createDictionary();
}

void BalanceWidget::updateBalance(int inc, int dec) {
    if (inc > 0) {
        userBalance = userBalance + inc;
    }
    if (dec > 0) {
        userBalance = userBalance - dec;
    }
}

void BalanceWidget::updateBalanceSDKChange(int newBalance) {
    userBalance = newBalance;
    userBalanceLabel->setText(QString(QString::number(userBalance) + " XCoin"));
}

void BalanceWidget::deleteWidgets() {
    QLayoutItem* item;
    while (balanceGrid->count() != 0) {
        QLayoutItem* child = balanceGrid->takeAt(0);
        if (child->layout() != 0) {
            delete(child->layout());
        }
        else if (child->widget() != 0) {
            delete(child->widget());
        }
        delete child;
    }
}