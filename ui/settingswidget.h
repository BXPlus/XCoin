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
private:
    QWidget* profileWidget;
    QWidget* nameWidget;
    QWidget* infoWidget;
    QComboBox* choiceBox;
    QScrollArea* scrollArea;

    QLabel* firstName;
    QLabel* lastName;
    QLabel* profileInfo1;
    QLabel* profileInfo2;

    QVBoxLayout* mainLayout;
    QHBoxLayout* profileLayout;
    QVBoxLayout* infoLayout;
    QHBoxLayout* nameLayout;

signals:

};

#endif // SETTINGSWIDGET_H
