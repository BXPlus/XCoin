#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "custombutton.h"
#include "settingswidget.h"

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
    SettingsWidget* settingsWidget;
    QWidget* graphsWidget;
private slots:
    void go_page(int);
private:
    Ui::MainWindow *ui;
    void pop_login();
};
#endif // MAINWINDOW_H
