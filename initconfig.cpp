#include "initconfig.h"

InitConfig::InitConfig(QTranslator *t,QStringList langues,QWidget *parent) :
    QWidget(parent)
{

    setupUi(this);
    runAllEvent();
    translator = t;
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
    connect(parcourbutt, &QPushButton::clicked, this, &InitConfig::setPathImage);
    connect(buttonBox, &QDialogButtonBox::accepted,this,&InitConfig::validConfig);
    connect(comboLangues,&QComboBox::currentTextChanged,this,&InitConfig::setLanguage);
    connect(radiodef, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiofs, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiomax, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
    connect(radiopers, &QRadioButton::clicked,this,&InitConfig::setWindowSize);
}

void InitConfig::changeEvent(QEvent *event){
    if(event->type() == QEvent::LanguageChange){
        //titre
        setWindowTitle(tr("Options"));

        //parametre windowsize
        radiodef->setText("&"+tr("Par Defaut"));
        radiofs->setText("&"+tr("Plein écran"));
        radiomax->setText("&"+tr("Maximiser"));
        radiopers->setText("&"+tr("Personnaliser"));
        labelH->setText(tr("Hauteur"));
        labelL->setText(("Largeur"));
        groupBox->setWindowIconText(tr("Personnalisation"));

        //file image
        parcourbutt->setText(tr("Parcourir"));
        doss->setText(tr("Dossier des images"));

        //Langues
        /*comboLangues->setItemText(0,tr("Francais"));
        comboLangues->setItemText(1,tr("Anglais")); */

    }
}


void InitConfig::setWindowSize(){
    windowSizeReady = true;
    verifConfig();
}
void InitConfig::setLanguage(){

    languesReady = true;
    translator->load(":/"+comboLangues->currentText().toLower()+".qm");
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
                //std::cout << "personalize " << hauteur->text().toStdString() << " " << largeur->text().toStdString() << std::endl;
            }

       }

        if(lineEdit->text().compare("") == 0){
            validInit = false;
        }else{
            settings.setValue("path",lineEdit->text());
        }



        settings.setValue("langue",comboLangues->currentText());

        if(validInit){
            settings.setValue("init","false");
            this->close();
            lang = settings.value("langue").toString();

            translator->load(":/"+lang.toLower()+".qm");

            mainWindowMenu *w = new mainWindowMenu(translator);
            w->show();
        }



}
