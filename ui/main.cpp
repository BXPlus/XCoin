#include "mainwindow.h"
#include "balancewidget.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <iostream>
#include "../XNode/XNodeSDK.h"
#include "../XNode/node.h"
#include <QtConcurrent/QtConcurrent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // load global stylesheet

        // extracting stylesheet path
    QString path = a.applicationDirPath();
    int index = path.indexOf("XCoin");
    QString subPath = path.mid(0,index+5);
    subPath.append("/ui/style.qss");

        // loading
    QFile qss(subPath);
    qss.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qss.readAll());
    a.setStyleSheet(styleSheet);
    qss.close();

    spdlog::set_level(spdlog::level::debug);

    XNodeSDK* xcoinClientSdkInstance = new XNodeSDK();
    xcoin::Node::getInstance().setSdkInstance(xcoinClientSdkInstance);

    MainWindow w;
    w.show();

    std::vector<std::string> DNSS = std::vector<std::string>();
    for(int i = 1; i < argc; i++ )
        DNSS.emplace_back(argv[i]);

    QFuture<void> future = QtConcurrent::run([=]() {
        xcoin::Node::getInstance().RunNode(DNSS);
    });

    return a.exec();
}



