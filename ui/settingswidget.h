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

    QVBoxLayout* finalLayout;
    QVBoxLayout* mainLayout;
    QHBoxLayout* nodePortLayout;
    QHBoxLayout* rDNSaddLayout;
    QHBoxLayout* publicaddLayout;
    QHBoxLayout* appearanceLayout;
    QHBoxLayout* flnodeLayout;

    QList<QVBoxLayout*> vList;
    QList<QLabel*> lList;
    QList<QLabel*> sList;
    QList<QAbstractButton*> bList;

    QLabel* nodePortString;
    QLabel* rDNSaddString;
    QLabel* publicaddString;
    QAbstractButton* appearanceBtn;
    QAbstractButton* flnodeBtn;

    QLabel* nodePortLabel;
    QLabel* rDNSaddLabel;
    QLabel* publicaddLabel;
    QLabel* appearanceLabel;
    QLabel* flnodeLabel;

    int flNode_count = 0;
    int appearance_count = 0;
private slots:
    void flnode_state();
    void appearance_state();
};

#endif // SETTINGSWIDGET_H
