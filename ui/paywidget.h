#ifndef PAYWIDGET_H
#define PAYWIDGET_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLineEdit>
#include <QSignalMapper>
#include "paycontactdialog.h"
#include <QList>

class PayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PayWidget(QWidget *parent = nullptr);

private:
    QMap<QString, QString> contactDict;
    QLabel* title;
    QVBoxLayout* pageLayout;
    QGridLayout* contactGrid;
    QWidget* boxContainer;
    QScrollArea* scrollContacts;
    QLineEdit* contactSearch;

    QWidget* topBox;
    QHBoxLayout* topLayout;

    void create_dictionary(QMap<QString, QString>);
    void contactSearchEdit();
    void deleteContact(int);
    void deleteWidgets();

private slots:
    void openPayDialog(QString value);
};

#endif // PAYWIDGET_H
