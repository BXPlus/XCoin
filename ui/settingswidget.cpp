#include "settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("border: 1px solid black");
    profileWidget = new QWidget(this);
    nameWidget = new QWidget(profileWidget);
    infoWidget = new QWidget(profileWidget);
//    profileWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    profileWidget->setMinimumSize(200, 200);

    choiceBox = new QComboBox(this);
//    choiceBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    choiceBox->setMinimumSize(200, 200);

    scrollArea = new QScrollArea(this);
//    scrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    scrollArea->setMinimumSize(100, 200);

    firstName = new QLabel("firstname");
    lastName = new QLabel("lastname");
    profileInfo1 = new QLabel("profileInfo1");
    profileInfo2 = new QLabel("profileInfo2");

    mainLayout = new QVBoxLayout(this);
    profileLayout = new QHBoxLayout(profileWidget);
    infoLayout = new QVBoxLayout(infoWidget);
    nameLayout = new QHBoxLayout(nameWidget);

    infoLayout->addWidget(profileInfo1);
    infoLayout->addWidget(profileInfo2);
    nameLayout->addWidget(firstName);
    nameLayout->addWidget(lastName);

    infoWidget->setLayout(infoLayout);
    nameWidget->setLayout(nameLayout);
    profileLayout->addWidget(nameWidget);
    profileLayout->addWidget(infoWidget);
    profileWidget->setLayout(profileLayout);

    mainLayout->addWidget(profileWidget);
    mainLayout->addWidget(choiceBox);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
}
