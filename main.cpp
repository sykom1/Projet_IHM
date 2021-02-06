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
    QString path;
    QString windowsize;
    string line;

    QString pathFileSettings = QApplication::applicationDirPath().left(1)+":/options.ini";
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, pathFileSettings);
    bool init = settings.value("init").toString().toStdString().compare("") == 0 ? true : false;
    QStringList langues = {"Francais","English"};
    //settings.setValue("langue", "");
    /*if(init){
        InitConfig *initconf = new InitConfig(&t,langues);
        initconf->show();

    } */

       lang = settings.value("langue").toString();

       t.load(":/"+lang.toLower()+".qm");






     a.installTranslator(&t);

    mainWindowMenu *w = new mainWindowMenu(&t);
    w->show();
    return a.exec();
}
