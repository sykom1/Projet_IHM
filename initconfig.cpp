#include "initconfig.h"

InitConfig::InitConfig(QStringList langues,QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle(tr("Options"));
    setupUi(this);
    runAllEvent();
    this->setWindowFlags(Qt::WindowTitleHint);
    groupBoxLangues->setStyleSheet("border : none");
    groupBoxSize->setStyleSheet("border : none");
    group.addButton(radiodef);
    group.addButton(radiofs);
    group.addButton(radiomax);
    group.addButton(radiopers);
    buttonBox->buttons().at(0)->setDisabled(true);
    hauteur->setValidator( new QIntValidator(0, 2000, this) );
    largeur->setValidator( new QIntValidator(0, 2000, this) );
    comboLangues->addItems(langues);
}

void InitConfig::runAllEvent(){
    connect(pushButton, &QPushButton::clicked, this, &InitConfig::setPathImage);
    connect(buttonBox, &QDialogButtonBox::accepted,this,&InitConfig::validConfig);
   // connect(radiofr, &QRadioButton::clicked,this,&InitConfig::setLanguage);
    //connect(radioeng, &QRadioButton::clicked,this,&InitConfig::setLanguage);
    connect(radiodef, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiofs, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiomax, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiopers, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
}

void InitConfig::setWindowSize(){
    windowSizeReady = true;
    verifConfig();
}
void InitConfig::setLanguage(){

    languesReady = true;
    verifConfig();
}
void InitConfig::setPathImage(){
    pathDirImage = QFileDialog::getExistingDirectory(this, tr("Choisir un dossier"),
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    lineEdit->setText(pathDirImage);
    lineEdit->setEnabled(true);
    pathReady = true;
    verifConfig();
}

void InitConfig::verifConfig(){
    if(languesReady && windowSizeReady && pathReady){
        buttonBox->buttons().at(0)->setDisabled(false);
    }
}
void InitConfig::validConfig(){
    bool validInit = true;
    QString pathFileSettings = QApplication::applicationDirPath().left(1)+":/options.ini";
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, pathFileSettings);


        // on recupère les valeurs des boutons pour écrire dans le fichier settings

        if(group.checkedButton() == radiodef){
            std::cout << "salut" << std::endl;
            settings.setValue("size","default");
        }
        else if(group.checkedButton() == radiomax){
            settings.setValue("size","maximised");
        }
        else if(group.checkedButton() == radiofs){
            settings.setValue("size","fullscreen");
        }
        else if(group.checkedButton() == radiopers){
            if(hauteur->text().compare("") == 0 || largeur->text().compare("") == 0){
                validInit = false;
            }else{
                settings.setValue("size","personalize " + hauteur->text() + " " + largeur->text());
                std::cout << "personalize " << hauteur->text().toStdString() << " " << largeur->text().toStdString() << std::endl;
            }

       }
        if(lineEdit->text().compare("") == 0){
            validInit = false;
        }else{
            settings.setValue("path",lineEdit->text());
        }

        if(validInit){
            this->close();
             // lancer l'application
        }




}
