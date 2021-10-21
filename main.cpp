#include "block.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Block w;
    w.show();
    return a.exec();
}
