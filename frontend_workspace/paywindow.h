#ifndef PAYWINDOW_H
#define PAYWINDOW_H
#include "mainwindow.h"

#include <QMainWindow>

namespace Ui {
class PayWindow;
}

class PayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PayWindow(QWidget *parent = nullptr);
    ~PayWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PayWindow *ui;
    MainWindow *mainwindow;
};

#endif // PAYWINDOW_H
