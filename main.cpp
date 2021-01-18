#include "mainwindowmenu.h"
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QTranslator t;

    QStringList languages;
    languages << "Français" << "English";

    QString lang = QInputDialog::getItem(NULL,"Selectionnez La Langue",
                                                        "Langage",languages);

    if( lang == "English"){
        t.load(":/english.qm");

    }

    else if( lang != "Français"){

        printf("Cette langue n'existe pas \n");
        return 0;
    }
     a.installTranslator(&t);
    mainWindowMenu w;
    w.show();
    return a.exec();
}
