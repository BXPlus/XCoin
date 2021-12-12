#include "mainwindow.h"
#include "balancewidget.h"
#include <QApplication>
#include <QFile>
#include <QDir>

#include <QDebug>
#include <iostream>

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
    return a.exec();
}



