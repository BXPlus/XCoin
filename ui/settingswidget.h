#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include "mainwindow.h"
#include <QComboBox>
#include <QScrollArea>
#include <QLineEdit>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parentWidget = nullptr);
    QPushButton* get_homeBtn();
    QWidget* mainWindow;
private:
    QWidget* mainWidget;
    QWidget* topBox;
    QWidget* emptyWidget;

    QVBoxLayout* mainLayout;
    QHBoxLayout* topLayout;
    QLabel* title;

    QList<QHBoxLayout*> hList;
    QList<QLabel*> lList = {};
    QList<QLabel*> sList = {};
    QList<QAbstractButton*> bList= {};
    QList<QString> stringList;
    QList<QWidget*> widgetList;
    QList<QLineEdit*> lineList;

    QPushButton* editBtn;

    int flNode_count = 0;
    int appearance_count = 0;
    int counter = 0;
private slots:
    void flnode_state();
    void appearance_state();
    void edit_press();
};

#endif // SETTINGSWIDGET_H
