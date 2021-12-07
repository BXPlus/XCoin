#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include "mainwindow.h"
#include <QComboBox>
#include <QScrollArea>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    QPushButton* get_homeBtn();
private:
    QWidget* mainWidget;

    QVBoxLayout* mainLayout;
    QWidget* emptyWidget;

    QList<QHBoxLayout*> hList;
    QList<QLabel*> lList = {};
    QList<QLabel*> sList = {};
    QList<QAbstractButton*> bList= {};
    QList<QString> stringList;

    int flNode_count = 0;
    int appearance_count = 0;
private slots:
    void flnode_state();
    void appearance_state();
};

#endif // SETTINGSWIDGET_H
