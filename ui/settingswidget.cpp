#include "settingswidget.h"
#include <QScrollArea>
#include <QDir>
#include <QtDebug>

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent)
{
  /* Ideas for the different elements of the settings page:
        - Node Port(un nombre)
        - Full/Light node (toggle)
        - Public address (string)
        - Root DNS address (string)
        - Appearance
        -*/
    stringList = {"Node Port:", "Root DNS address:", "Public address:"
                 , "Full/Light node:", "Dark/Light mode:", "30140",
                 "123.456.78.90", "202.25.1.3"};

    mainLayout = new QVBoxLayout(this);
    emptyWidget = new QWidget(this);

    for (int i = 0; i < 5; i++) {
        QHBoxLayout* layout = new QHBoxLayout();
        hList.append(layout);

        QLabel* label = new QLabel(stringList[i], this);
        label->setObjectName("settingslabel");
        lList.append(label);

        layout->addWidget(label);

        if (i <= 2) {
            QLabel* string = new QLabel(stringList[i+5], this);
            string->setObjectName("settingsstring");
            sList.append(string);
            layout->addWidget(string);
        }
        else {
            ToggleBtn* btn = new ToggleBtn(10, 10, this);
            bList.append(btn);
            layout->addWidget(btn);
        }
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        mainLayout->addLayout(layout, 12);
    }

    mainLayout->addWidget(emptyWidget, 40);

    setLayout(mainLayout);

    connect(bList[0], SIGNAL(clicked(bool)), this, SLOT(flnode_state()));
    connect(bList[1], SIGNAL(clicked(bool)), this, SLOT(appearance_state()));
}

void SettingsWidget::flnode_state()
{
    if (flNode_count % 2 == 0) {
        flNode_count ++;
        qDebug() << "flnode : on";
    }
    else {
        flNode_count ++;
        qDebug() << "flnode : off";
    }
}

void SettingsWidget::appearance_state()
{
    if (appearance_count % 2 == 0) {
        appearance_count ++;
        qDebug() << "appearance : on";
    }
    else {
        appearance_count ++;
        qDebug() << "appearance : off";
    }
}
