#include "custombutton.h"
#include <QDebug>
#include <QMessageBox>

void CustomButton::ActionDuBoutton()
{
    QMessageBox::information(this, "Toto", "Ceci est un message du bouton" + m_text);
}

CustomButton::CustomButton(QString text, QWidget *parent)
    :QPushButton(parent), m_text(text)
{
    setText(m_text);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

CustomButton::~CustomButton()
{
   qDebug() << "Destruction !" << endl;
}
