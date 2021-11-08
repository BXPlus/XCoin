#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include "paywindow.h"
#include "balancewindow.h"
#include "contactswindow.h"
#include "livewindow.h"
#include "graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_btnPay_clicked();
    void on_btnBalance_clicked();

    void on_btnContacts_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    PayWindow *paywindow;
    BalanceWindow *balancewindow;
    ContactsWindow *contactswindow;
    LiveWindow *livewindow;
    GraphWindow *graphwindow;
};
#endif // MAINWINDOW_H
