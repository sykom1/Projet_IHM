#include "mainwindowmenu.h"
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QTranslator t;

    QStringList languages;
    languages << "Francais" << "English";
    QString lang;
    fstream myfile;
    myfile.open ("options.txt");
    string line;

    if( myfile.tellg() == 0 ){

        lang = QInputDialog::getItem(NULL,"Selectionnez La Langue",
                                                           "Langage",languages);
        std::cout << "on passe ici" << std::endl;
        std::cout << lang.toStdString() << std::endl;

        myfile << lang.toStdString();
        myfile.close();
    }else{
          if (myfile.is_open())
          {
              std::cout << "On passe plutot ici" << std::endl;
              std::cout << lang.toStdString();
            while (getline(myfile,line) )
            {
              lang = QString::fromStdString(lang.toStdString());
            }
            myfile.close();
          }

          else cout << "Unable to open file";
      }


    if( lang == "English"){
        t.load(":/english.qm");

    }

    else if( lang != "Francais"){

        printf("Cette langue n'existe pas \n");
        return 0;
    }



     a.installTranslator(&t);

    mainWindowMenu *w = new mainWindowMenu(&t);
    w->show();
    return a.exec();
}
