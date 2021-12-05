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
    QAbstractButton* appearanceBtn;
    QAbstractButton* flNode;

    QLabel* nodePort;
    QLabel* rDNSadd;
    QLabel* publicadd;

signals:

};

#endif // SETTINGSWIDGET_H
