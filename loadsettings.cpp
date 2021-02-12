#include "loadsettings.h"

LoadSettings::LoadSettings(QMainWindow *mainWindow, QTranslator *translator)
{
    QString pathFileSettings = QApplication::applicationDirPath().left(1)+":/options.ini";
    settings = new QSettings(QSettings::NativeFormat, QSettings::UserScope, pathFileSettings);
    this->mainWindow = mainWindow;
    this->translator = translator;
}

void LoadSettings::loadAllConfig(){
    loadSizeOnTheMainWindow();
    loadLanguageOnTheApp();
    loadPathFileForImg();
}

QString LoadSettings::getPathFileForImg(){
    return pathFileForImg;
}


void LoadSettings::loadSizeOnTheMainWindow(){
    QString configSize = settings->value("size").toString();
    QRect rect = QGuiApplication::screens().at(0)->geometry();
    mainWindow->showNormal();
    if(configSize.compare("maximised")==0){
        mainWindow->move(0, 0);
        mainWindow->setFixedWidth(rect.width());
        mainWindow->setFixedHeight(rect.height());
    }else if(configSize.compare("fullscreen")==0){
        mainWindow->showFullScreen();
    }
    else if(configSize.compare("default")!=0){
        mainWindow->move(0, 0);
        mainWindow->resize(configSize.split(" ")[2].toInt(), configSize.split(" ")[1].toInt());
    }
}

void LoadSettings::loadLanguageOnTheApp(){
    QString loadLang = settings->value("langue").toString();
    translator->load(":/"+loadLang.toLower()+".qm");
}

void LoadSettings::loadPathFileForImg(){
    pathFileForImg = settings->value("path").toString();
}
