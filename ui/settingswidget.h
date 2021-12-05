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
    QWidget* profileWidget;
    QWidget* nameWidget;
    QWidget* infoWidget;
    QWidget* hWidget;
    QPushButton* goHomeBtn;
    QComboBox* choiceBox;
    QScrollArea* scrollArea;

    QLabel* firstName;
    QLabel* lastName;
    QLabel* profileInfo1;
    QLabel* profileInfo2;
    QLabel* goHomeLabel;

    QVBoxLayout* mainLayout;
    QHBoxLayout* profileLayout;
    QVBoxLayout* infoLayout;
    QHBoxLayout* nameLayout;
    QHBoxLayout* hLayout;

    QList<QWidget*> boxList;

signals:

};

#endif // SETTINGSWIDGET_H
