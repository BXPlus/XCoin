#include "addcontactdialog.h"

addContactDialog::addContactDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Add Contact");

    mainLayout = new QVBoxLayout(this);
    sList = {"First Name:", "Last Name", "Public Key:"};

    for (int i = 0; i < 3; i++) {
        QHBoxLayout* layout = new QHBoxLayout();
        layoutList.append(layout);

        QLabel* label = new QLabel(sList[i], this);
        labelList.append(label);
        label->setObjectName("addContact");

        QLineEdit* line = new QLineEdit();
        lineList.append(line);

        layout->addWidget(label);
        layout->addWidget(line);

        mainLayout->addLayout(layout, 25);
    }
    addBtn = new CustomButton("Done", this);
    addBtn->setObjectName("addContactBtn");

    connect(addBtn, SIGNAL(clicked(bool)), this, SLOT(closed()));

    mainLayout->addWidget(addBtn, 25);
    setLayout(mainLayout);
}

addContactDialog::~addContactDialog()
{
}

QList<QString> addContactDialog::get_info()
{
    if (click){
        return {"true", lineList[0]->text(), lineList[1]->text(), lineList[2]->text()};
    }
    return {"false", lineList[0]->text(), lineList[1]->text(), lineList[2]->text()};
}

void addContactDialog::closed()
{
    click = true;
    this->close();
}
