#ifndef BALANCEWIDGET2_H
#define BALANCEWIDGET2_H

#include <QWidget>
#include <QTabWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QMap>

class BalanceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BalanceWidget(QWidget *parent = nullptr);
private:
    QTabWidget* tabWidget;
    QVBoxLayout* mainLayout;

    QWidget* bWidget;
    QHBoxLayout* balanceLayout;

    QList<QWidget*> tabList;
    QList<QVBoxLayout*> layoutList;
    QList<QString> titleList;
    QList<QString> balanceList;
    QList<QLabel*> labelList;
    QList<QString> typeList;
    QList<QString> amountList;

    QGridLayout* balanceGrid;
    QWidget* boxContainer;
    QScrollArea* scrollBalance;
    QMap<QString, QString> balanceDict;
};

#endif // BALANCEWIDGET2_H
