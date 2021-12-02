#include "settingswidget.h"
#include <QScrollArea>
#include <QDir>

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent)
{
  /* Ideas for the different pages of the settings page:
        -Notifications
        -Appearance
        -*/

    //ComboBox Setup
    choiceBox = new QComboBox(this);

    // Scroll Area Setup
    QWidget* roundBox = new QWidget(this);
    scrollArea = new QScrollArea(roundBox);
    scrollArea->horizontalScrollBar();
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("background-color: grey;");

    QBoxLayout* accessBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom, roundBox);
    accessBoxLayout->addWidget(scrollArea);
    accessBoxLayout->setAlignment(scrollArea, Qt::AlignHCenter);

    QWidget* boxContainer = new QWidget(scrollArea);
    QVBoxLayout* boxLayout = new QVBoxLayout{boxContainer};
    scrollArea->setWidget(boxContainer);

    boxContainer->resize(600, 300);

    for (int i = 0; i < 4; i++) {
        QWidget* box = new QWidget(boxContainer);
        box->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        box->setObjectName("boxscroll");

        boxList.append(box);
        boxLayout->addWidget(box);
    }

    //Profile Widget Setup
    profileWidget = new QWidget(this);
    nameWidget = new QWidget(profileWidget);
    infoWidget = new QWidget(profileWidget);

    firstName = new QLabel("firstname");
    lastName = new QLabel("lastname");
    profileInfo1 = new QLabel("profileInfo1");
    profileInfo2 = new QLabel("profileInfo2");

    profileLayout = new QHBoxLayout(profileWidget);
    infoLayout = new QVBoxLayout(infoWidget);
    nameLayout = new QHBoxLayout(nameWidget);

        //XCoin Logo
        QWidget* logoWidget = new QWidget(profileWidget);
        QString path = QDir::currentPath();
        int index = path.indexOf("XCoin");
        QString subPath = path.mid(0,index+5);
        subPath.append("/ui/SettingsIcon.png");

        QPixmap pic(subPath);
        QLabel* imgLabel = new QLabel(logoWidget);
        imgLabel->setAlignment(Qt::AlignCenter);
        imgLabel->setFixedSize(200, 200);
        imgLabel->setPixmap(pic);

    infoLayout->addWidget(profileInfo1);
    infoLayout->addWidget(profileInfo2);
    nameLayout->addWidget(firstName);
    nameLayout->addWidget(lastName);

    infoWidget->setLayout(infoLayout);
    nameWidget->setLayout(nameLayout);
    profileLayout->addWidget(logoWidget);
    profileLayout->addWidget(nameWidget);
    profileLayout->addWidget(infoWidget);
    profileWidget->setLayout(profileLayout);

    //Main Layout Setup
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(profileWidget, 50);
    mainLayout->addWidget(choiceBox, 15);
    mainLayout->addWidget(roundBox, 35);

    setLayout(mainLayout);
}
