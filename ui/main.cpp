#include "mainwindow.h"
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
    qDebug() << "Stylesheet path: " << subPath;

        // loading
    QFile qss(subPath);
    qss.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qss.readAll());
    a.setStyleSheet(styleSheet);
    qss.close();

    MainWindow w;
    w.show();
    return a.exec();

    //Login page
    PaymentDialog *payment_window = new PaymentDialog();
    payment_window->setModal(true);
    payment_window->exec();
    bool identified = payment_window->get_identified();

    if (identified) {
        PaymentDialog P;
        P.show();
        return a.exec();
    }
}

}
