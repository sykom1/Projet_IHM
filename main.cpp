#include "mainwindowmenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindowMenu w;
    w.show();
    return a.exec();
}
