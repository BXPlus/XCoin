#ifndef BALANCEWIDGET_H
#define BALANCEWIDGET_H

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
    void createDictionary();
    void deleteWidgets();

public slots:
    void editBalanceDict(QString object, QString amount);
    void updateBalanceSDKChange(int newBalance = 0);

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
    QLabel* userBalanceLabel;
    QList<QString> typeList;
    QList<QString> amountList;
    QWidget* boxContainer;
    QScrollArea* scrollBalance;
    QMap<QString, QString> balanceDict;
    QGridLayout* balanceGrid;
    QVBoxLayout* smallLayout;
    QVBoxLayout* bigLayout;

    void updateBalance(int, int);
    int userBalance;
};

#endif // BALANCEWIDGET_H
