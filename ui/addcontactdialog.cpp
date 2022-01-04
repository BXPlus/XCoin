#include "addcontactdialog.h"

addContactDialog::addContactDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Add Contact");
    this->setStyleSheet("background-color: white;");
    this->setFixedSize(200, 300);

    mainLayout = new QVBoxLayout(this);
    sList = {"First Name:", "Last Name", "Public Key:"};

    for (int i = 0; i < 3; i++) {
        QVBoxLayout* layout = new QVBoxLayout();
        layoutList.append(layout);

        QLabel* label = new QLabel(sList[i], this);
        labelList.append(label);
        label->setObjectName("addContact");

        QLineEdit* line = new QLineEdit();
        lineList.append(line);
        line->setStyleSheet("color: black;"
                                "border: 1px solid gray;"
                                "border-radius: 4px;"
                                "padding: 5px;"
                                "margin-bottom: 5px;");

        layout->addWidget(label);
        layout->addWidget(line);

        mainLayout->addLayout(layout, 25);
    }
    addBtn = new QPushButton("Done", this);
    addBtn->setObjectName("addContactBtn");
    addBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    addBtn->setStyleSheet("color: white;"
                                    "background-color: rgba(109, 223, 129, 255);"
                                    "background-color: green;"
                                    "border-radius: 4px;"
                                    "padding: 5px;"
                                    "margin-top: 5px;");

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
