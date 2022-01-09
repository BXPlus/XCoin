#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDebug>
#include "balancewidget.h"
#include "custombutton.h"
#include "contactswidget.h"
#include "homewidget.h"
#include "logindialog.h"
#include "settingswidget.h"
#include "addcontactdialog.h"
#include "balancewidget.h"
#include "../XNode/node.h"
#include "../XNode/XNodeSDK.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int getUserBalance();
    void editUserBalance(int, int);
private:
    QList<CustomButton*> btnList;

    QWidget* mainWidget;
    QWidget* menuContainer;
    QHBoxLayout* mainLayout;
    QStackedWidget* contentContainer;
    QVBoxLayout* menuLayout;

    QWidget* homeWidget;
    QWidget* balanceWidget;
    QWidget* contactsWidget;
    QWidget* settingsWidget;

    int style = 0;
    void toggleStyleSheet();

private slots:
    void go_home();
    void go_page(int);
protected:
    void closeEvent(QCloseEvent * event);

private:
    QLabel* balanceLabel;
    int userBalance;
    void updateUserBalanceFromSDK(int newBalance){
        userBalance = newBalance;
        balanceLabel->setText(QString::number(userBalance));
    };
};
#endif // MAINWINDOW_H