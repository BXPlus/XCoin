#include "settingswidget.h"
#include <QScrollArea>
#include <QDir>

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent)
{
  /* Ideas for the different pages of the settings page:
        - Node Port(un nombre)
        - Full/Light node (toggle)
        - Public address (string)
        - Root DNS address (string)
        - Appearance
        -*/

    //Header of Settings page setup
    hWidget = new QWidget(this);

        //Go Back Button Setup
        goHomeBtn = new QPushButton(hWidget);

        QString path = QDir::currentPath();
        int index = path.indexOf("XCoin");
        QString subPath = path.mid(0,index+5);
        subPath.append("/ui/GoBackArrow.png");

        QPixmap pic(subPath);
        QIcon ButtonIcon(pic);
        goHomeBtn->setIcon(ButtonIcon);
        goHomeBtn->setIconSize(pic.rect().size());

        //Layouts Setup
        goHomeLabel = new QLabel("go Home", hWidget);
        hLayout = new QHBoxLayout(hWidget);
        hLayout->addWidget(goHomeBtn, 20);
        hLayout->addWidget(goHomeLabel, 80);
        hWidget->setLayout(hLayout);

    //Combo Box Setup
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

        //Settings Logo
        QWidget* logoWidget = new QWidget(profileWidget);
        QString path2 = QDir::currentPath();
        int index2 = path2.indexOf("XCoin");
        QString subPath2 = path2.mid(0,index2+5);
        subPath2.append("/ui/SettingsIcon.png");

        QPixmap pic2(subPath2);
        QLabel* imgLabel2 = new QLabel(logoWidget);
        imgLabel2->setAlignment(Qt::AlignCenter);
        imgLabel2->setFixedSize(200, 200);
        imgLabel2->setPixmap(pic2);

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
    mainLayout->addWidget(hWidget, 10);
    mainLayout->addWidget(profileWidget, 45);
    mainLayout->addWidget(choiceBox, 12);
    mainLayout->addWidget(roundBox, 33);

    setLayout(mainLayout);
}

QPushButton* SettingsWidget::get_homeBtn()
{
    return goHomeBtn;
}
