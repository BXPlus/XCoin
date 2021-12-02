#include "contactswidget.h"

ContactsWidget::ContactsWidget(QWidget *parent)
{
    title = new QLabel(this);
    title->setText("My Contacts");
    title->setObjectName(QString("title"));
}
