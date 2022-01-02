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

    XNodeSDK* xcoinClientSdkInstance = new XNodeSDK();
    xcoin::Node::getInstance().setSdkInstance(xcoinClientSdkInstance);

    //Login page
//    LoginDialog *dialogLogin = new LoginDialog();
//    dialogLogin->setModal(true);
//    dialogLogin->exec();
//    bool identified = dialogLogin->get_identified();

//    if (identified) {
//        MainWindow w;
//        w.show();
//        return a.exec();
//    }

    //Économiser les doigts de picha en evitant d'avoir à cliquer à chaque fois sur le login
    MainWindow w;
    w.show();

    auto dnss = std::vector<std::string>();
    //dnss.push_back("192.168.1.525:3000"); // TODO: Add DNSS from config file here

    QFuture<void> future = QtConcurrent::run([=]() {
        xcoin::Node::getInstance().RunNode(dnss);
    });

    return a.exec();
}



