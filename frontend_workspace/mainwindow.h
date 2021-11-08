#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include "balancedialog.h"
#include "paywindow.h"

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
    void contacts();
    void on_btnBalance_clicked();

    void on_btnPay_clicked();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *contact_animation;
    BalanceDialog *balancedial;
    PayWindow *paywindow;
};
#endif // MAINWINDOW_H
