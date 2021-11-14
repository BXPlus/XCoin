#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    QWidget* mainWidget, menuContainer;
    QHBoxLayout* mainLayout;
    QStackedWidget* contentContainer;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
