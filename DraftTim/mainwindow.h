#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "custombutton.h"
#include "login.h"
#include <QHBoxLayout>
#include <QStackedWidget>

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
    void go_home();
    void go_balance();
    void go_payments();
    void go_contacts();
    void go_updates();
    void go_graphs();
    bool pop_login();
private:
    Ui::MainWindow *ui;

    QList<CustomButton*> ListBtn;
    QList<QWidget*> ListPages;
    QDialog* dialog_login;

    QHBoxLayout *hbtn_layout;
    QVBoxLayout *og_layout;
    QHBoxLayout *home_layout;
    QLayout *balance_layout;
    QLayout *payments_layout;
    QLayout *contacts_layout;
    QLayout *updates_layout;
    QLayout *graphs_layout;

    QWidget *m_widget;
    QWidget *hbtn_widget;
    QStackedWidget *m_swidget;

    QWidget* home_widget;
    QWidget* balance_widget;
    QWidget* payments_widget;
    QWidget* contacts_widget;
    QWidget* updates_widget;
    QWidget* graphs_widget;
};
#endif // MAINWINDOW_H
