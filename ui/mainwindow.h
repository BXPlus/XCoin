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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    int getUserBalance();
    void editUserBalance(int, int);

private slots:
    void go_home();
    void go_page(int);
protected:
    void closeEvent(QCloseEvent * event);

private:
    Ui::MainWindow *ui;
    QLabel* balanceLabel;
    int userBalance;
    void updateUserBalanceFromSDK(int newBalance){userBalance = newBalance;};
};
#endif // MAINWINDOW_H