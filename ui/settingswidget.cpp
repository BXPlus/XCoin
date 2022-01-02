#include "settingswidget.h"
#include <QScrollArea>
#include <QDir>
#include <QtDebug>
#include <QApplication>

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent)
{
  /* Ideas for the different elements of the settings page:
        - Node Port(un nombre)
        - Full/Light node (toggle)
        - Public address (string)
        - Root DNS address (string)
        - Appearance
        -*/
    this->mainWindow = parent;

    //Header Setup
    topBox = new QWidget();
    topLayout = new QHBoxLayout();
    topBox->setLayout(topLayout);

    title = new QLabel(this);
    title->setText("Settings");
    title->setObjectName(QString("title"));
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    editBtn = new QPushButton("Edit", this);
    editBtn->setObjectName("menuBtn");
    editBtn->setMaximumSize(55, 45);

    connect(editBtn, SIGNAL(clicked(bool)), this, SLOT(edit_press()));

    topLayout->addWidget(title);
    topLayout->addWidget(editBtn, 0, Qt::AlignRight);

    //Settings page actual setup
    stringList = {"Node Port:", "Root DNS address:", "Public address:"
                 , "Full/Light node:", "Dark/Light mode:", "30140",
                 "123.456.78.90", "202.25.1.3"};

    mainLayout = new QVBoxLayout(this);
    emptyWidget = new QWidget(this);

    mainLayout->addWidget(topBox);

    for (int i = 0; i < 5; i++) {
        QWidget* widget = new QWidget(this);
        widgetList.append(widget);
        widget->setObjectName("settingswidget");

        QHBoxLayout* layout = new QHBoxLayout();
        hList.append(layout);

        QLabel* label = new QLabel(stringList[i], this);
        label->setObjectName("settingslabel");
        lList.append(label);
        label->setMaximumSize(130, 30);

        layout->addWidget(label, 0, Qt::AlignLeft);

        if (i <= 2) {
            QLabel* string = new QLabel(stringList[i+5], this);
            string->setObjectName("settingsstring");
            sList.append(string);

            QLineEdit* lineEdit = new QLineEdit(this);
            lineList.append(lineEdit);
            lineEdit->setVisible(false);

            layout->addWidget(string, 0, Qt::AlignRight);
            layout->addWidget(lineEdit, 0, Qt::AlignRight);
        }
        else {
//            ToggleBtn* btn = new ToggleBtn(10, 10, this);
//            bList.append(btn);
//            layout->addWidget(btn, 0, Qt::AlignRight);
        }
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        widget->setLayout(layout);

        mainLayout->addWidget(widget, 12);
    }

    mainLayout->addWidget(emptyWidget, 40);

    setLayout(mainLayout);

    // connect(bList[0], SIGNAL(clicked(bool)), this, SLOT(flnode_state()));
    // connect(bList[1], SIGNAL(clicked(bool)), this, SLOT(appearance_state()));
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
    appearance_count ++;
    if (appearance_count % 2 == 0) {
        qDebug() << "appearance : off";
        QString path = qApp->applicationDirPath();
        int index = path.indexOf("XCoin");
        QString subPath = path.mid(0,index+5);
        subPath.append("/ui/style.qss");

            // loading
        QFile qss(subPath);
        qss.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(qss.readAll());
        qApp->setStyleSheet(styleSheet);
        qss.close();
    }
    else {
        qDebug() << "appearance : on";
        QString path = qApp->applicationDirPath();
        int index = path.indexOf("XCoin");
        QString subPath = path.mid(0,index+5);
        subPath.append("/ui/styleLight.qss");

            // loading
        QFile qss(subPath);
        qss.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(qss.readAll());
        qApp->setStyleSheet(styleSheet);
        qss.close();
    }
}

void SettingsWidget::edit_press()
{
    if (counter % 2 == 0) {
        editBtn->setText("Done");
        editBtn->setMaximumWidth(63);

        for (int i = 0; i < 2; i++) {
            QLineEdit* lineEdit = lineList[i];
            QLabel* label = sList[i];

            lineEdit->setVisible(true);
            label->setVisible(false);
            lineEdit->setText(label->text());
        }
    }
    else {
        editBtn->setText("Edit");
        editBtn->setMaximumWidth(55);

        for (int i = 0; i < 2; i++) {
            QLineEdit* lineEdit = lineList[i];
            QLabel* label = sList[i];

            lineEdit->setVisible(false);
            label->setVisible(true);
            label->setText(lineEdit->text());
        }
    }
    counter++;
}
