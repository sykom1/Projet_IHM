#include "initconfig.h"

InitConfig::InitConfig(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    runAllEvent();
    this->setWindowFlags(Qt::WindowTitleHint);
    groupBoxLangues->setStyleSheet("border : none");
    groupBoxSize->setStyleSheet("border : none");

}

void InitConfig::runAllEvent(){
    connect(pushButton, &QPushButton::clicked, this, &InitConfig::setPathImage);
    connect(buttonBox, &QDialogButtonBox::accepted,this,&InitConfig::validConfig);
}

void InitConfig::setWindowSize(){

}
void InitConfig::setLanguage(){


}
void InitConfig::setPathImage(){
    pathDirImage = QFileDialog::getExistingDirectory(this, tr("Choisir un dossier"),
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    lineEdit->setText(pathDirImage);
    lineEdit->setEnabled(true);
}
void InitConfig::validConfig(){
    //vérifier que toutes les boxs sont cochées
    // on recupère les valeurs des boutons pour écrire dans le fichier settings
    this->close();
    // lancer l'application

}
