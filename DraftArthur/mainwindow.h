#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "balancebutton.h"
#include "contactbutton.h"
#include "graphbutton.h"
#include "homebutton.h"
#include "livebutton.h"
#include "paybutton.h"
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //QList<QPushButton*> listbtn;
    QVBoxLayout* m_vLayout;
    QWidget* mainwidget;
};
#endif // MAINWINDOW_H
