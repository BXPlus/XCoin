#include "settingswidget.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    setStyleSheet("QWidget {border: 1px solid white}");
    ui->setupUi(this);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}
