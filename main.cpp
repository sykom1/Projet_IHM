#include "mainwindowmenu.h"
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>
#include <iostream>
#include <string>
#include "initconfig.h"
using namespace std;



int main(int argc, char *argv[])
{



    QApplication a(argc, argv);

    QTranslator t;

    QStringList languages;
    languages << "Francais" << "English";
    QString lang;
    string line;

    QString pathFile = QApplication::applicationDirPath().left(1)+":/options.ini";
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, pathFile);
    //settings.setValue("langue", "");
    if(settings.value("langue").toString().toStdString().compare("")==0){
        lang = QInputDialog::getItem(NULL,"Selectionnez La Langue",
                                                           "Langage",languages);
        settings.setValue("langue", lang);
    }else{
        lang = settings.value("langue").toString();
    }

    t.load(":/"+lang.toLower()+".qm");
    /*InitConfig initconf;
    initconf.show(); */




     a.installTranslator(&t);

    mainWindowMenu *w = new mainWindowMenu(&t);
    w->show();
    return a.exec();
}
