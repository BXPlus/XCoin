#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "custombutton.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "customwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


   private:

    CustomWidget* m_customWidget;

    QWidget* m_central;
    QVBoxLayout* m_vLayout;

};
#endif // MAINWINDOW_H
