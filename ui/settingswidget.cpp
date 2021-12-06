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
    mainLayout = new QVBoxLayout(this);
    nodePortLayout = new QHBoxLayout();
    rDNSaddLayout = new QHBoxLayout();
    publicaddLayout = new QHBoxLayout();
    appearanceLayout = new QHBoxLayout();
    flnodeLayout = new QHBoxLayout();

    nodePortLabel = new QLabel("Node Port:", this);
    flnodeLabel = new QLabel("Full/Light node:", this);
    publicaddLabel = new QLabel("Public address:", this);
    rDNSaddLabel = new QLabel("Root DNS address:", this);
    appearanceLabel = new QLabel("Dark/Light mode:", this);

    nodePortString = new QLabel("30140", this);
    rDNSaddString = new QLabel("123.456.78.90", this);
    publicaddString = new QLabel("202.25.1.3", this);
    flnodeBtn = new ToggleBtn(10, 10, this);
    appearanceBtn = new ToggleBtn(10, 10, this);

    nodePortLayout->addWidget(nodePortLabel);
    nodePortLayout->addWidget(nodePortString);

    rDNSaddLayout->addWidget(rDNSaddLabel);
    rDNSaddLayout->addWidget(rDNSaddString);

    publicaddLayout->addWidget(publicaddLabel);
    publicaddLayout->addWidget(publicaddString);

    appearanceLayout->addWidget(appearanceLabel);
    appearanceLayout->addWidget(appearanceBtn);

    flnodeLayout->addWidget(flnodeLabel);
    flnodeLayout->addWidget(flnodeBtn);

    mainLayout->addLayout(nodePortLayout);
    mainLayout->addLayout(rDNSaddLayout);
    mainLayout->addLayout(publicaddLayout);
    mainLayout->addLayout(flnodeLayout);
    mainLayout->addLayout(appearanceLayout);

    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);

    mainWidget->setMaximumSize(300, 400);
    finalLayout = new QVBoxLayout(this);
    finalLayout->addWidget(mainWidget);
    setLayout(finalLayout);

    connect(flnodeBtn, SIGNAL(clicked(bool)), this, SLOT(flnode_state()));
    connect(appearanceBtn, SIGNAL(clicked(bool)), this, SLOT(appearance_state()));
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
