#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStackedWidget>
#include <QMainWindow>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* mainWidget;
    QHBoxLayout* mainLayout;
    QStackedWidget* contentContainer;

private:
    Ui::MainWindow *ui;
//private slots:
//    void isclicked();
};
#endif // MAINWINDOW_H
