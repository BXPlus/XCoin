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
    nodePort = new QLabel("Node Port:");
    flNode = new ToggleBtn(70, 100, this);
    //appearanceBtn = new ToggleBtn(this);
    rDNSadd = new QLabel("root DNS address");
    publicadd = new QLabel("public address");
}

//QPushButton* SettingsWidget::get_homeBtn()
//{
//    return goHomeBtn;
//}
