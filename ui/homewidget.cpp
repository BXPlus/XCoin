#include "homewidget.h"
#include <QLabel>
#include <QGraphicsWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QFontDatabase>
#include <QDir>

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent)
{
    pageLayout = new QVBoxLayout(this);
    pageLayout->setAlignment(Qt::AlignCenter);

    title = new QLabel(this);
    title->setText("Welcome back.");
    title->setObjectName(QString("title"));
    title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    // logo
    QString path = QDir::currentPath();
    int index = path.indexOf("XCoin");
    QString subPath = path.mid(0,index+5);
    subPath.append("/ui/xcoin.png");

    QPixmap pic(subPath);
    QLabel* imgLabel = new QLabel(this);
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setPixmap(pic);

    subtitle = new QLabel(this);
    subtitle->setText("Key #dk9174hdn57s");
    subtitle->setObjectName(QString("subtitle"));
    subtitle->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    subtitle->setMinimumWidth(300);

    XNodeSDK* xNodeInstance = xcoin::Node::getInstance().getSdkInstance();

    xNodeInstance->onStatusChanged = std::bind( &HomeWidget::handleNewNodeStatusFromSDK, this, std::placeholders::_1 );

    statusLabel = new QLabel(this);
    statusLabel->setText("...");
    statusLabel->setObjectName(QString("statusLabel"));
    statusLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    xNodeInstance->onStatusMessageBroadcast = std::bind(&HomeWidget::handleNewStatusMessageFromSDK, this, std::placeholders::_1);

    pageLayout->addWidget(imgLabel);
    pageLayout->addWidget(title);
    pageLayout->addWidget(subtitle);
    pageLayout->addWidget(statusLabel);
    this->setLayout(pageLayout);

}

void HomeWidget::handleNewNodeStatusFromSDK(XNodeSDK::XNodeStatus status) const{
    switch (status) {
        case XNodeSDK::WaitingForDNSS: subtitle->setText("Waiting for DNSS");
        case XNodeSDK::Down: subtitle->setText("Node is offline");
        case XNodeSDK::TerminatedWithError: subtitle->setText("Node was shutdown");
        case XNodeSDK::SyncingBlockchain: subtitle->setText("Blockchain is syncing");
        case XNodeSDK::Ready: subtitle->setText("Node is ready!");
    }
}

void HomeWidget::handleNewStatusMessageFromSDK(const std::string& message) {
    statusLabel->setText(QString::fromStdString(message));
}

HomeWidget::~HomeWidget()
{
}
