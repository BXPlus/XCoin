#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "custombutton.h"
#include "homewidget.h"
#include "payments.h"
#include "logindialog.h"
#include "settingswidget.h"
#include "togglebtn.h"

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
    QWidget* paymentsWidget;
    QWidget* contactsWidget;
    QWidget* settingsWidget;
    QWidget* graphsWidget;

private slots:
    void go_home();
    void go_page(int);
protected:
    void closeEvent(QCloseEvent * event);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
