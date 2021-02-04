#include "initconfig.h"

InitConfig::InitConfig(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    runAllEvent();
    this->setWindowFlags(Qt::WindowTitleHint);
    groupBoxLangues->setStyleSheet("border : none");
    groupBoxSize->setStyleSheet("border : none");
    group.addButton(radiodef);
    group.addButton(radiofs);
    group.addButton(radiomax);
    group.addButton(radiopers);

}

void InitConfig::runAllEvent(){
    connect(pushButton, &QPushButton::clicked, this, &InitConfig::setPathImage);
    connect(buttonBox, &QDialogButtonBox::accepted,this,&InitConfig::validConfig);
    connect(radiofr, &QRadioButton::clicked,this,&InitConfig::setLanguage);
    connect(radioeng, &QRadioButton::clicked,this,&InitConfig::setLanguage);
    connect(radiodef, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiofs, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiomax, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiopers, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
}

void InitConfig::setWindowSize(){
    windowSizeReady = true;
}
void InitConfig::setLanguage(){

    languesReady = true;
}
void InitConfig::setPathImage(){
    pathDirImage = QFileDialog::getExistingDirectory(this, tr("Choisir un dossier"),
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    lineEdit->setText(pathDirImage);
    lineEdit->setEnabled(true);
    pathReady = true;
}
void InitConfig::validConfig(){
    //vérifier que toutes les boxs sont cochées
    if(languesReady && windowSizeReady && pathReady){
        // on recupère les valeurs des boutons pour écrire dans le fichier settings

        if(group.checkedButton() == radiodef){
            std::cout << "salut" << std::endl;
        }
        else if(group.checkedButton() == radiomax){

        }
        else if(group.checkedButton() == radiofs){

        }
        else if(group.checkedButton() == radiopers){

        }


       this->close();
        // lancer l'application
    }



}
