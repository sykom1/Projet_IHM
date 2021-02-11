#include "menusettings.h"

MenuSettings::MenuSettings(QStringList langues, QTranslator *translator,
                           QVector<QVector<QAction*>*> *listOfListQAction, QWidget *parent) : QWidget(parent)
{
    layoutSettings = new QVBoxLayout();
    QString pathFileSettings = QApplication::applicationDirPath().left(1)+":/options.ini";
    settings = new QSettings(QSettings::NativeFormat, QSettings::UserScope, pathFileSettings);
    this->setLayout(layoutSettings);
    this->listOfListQAction = listOfListQAction;
    //this->languesDisplay = langues;
    for(int i=0; i<langues.size(); i++){
        if(settings->value("langue").toString().compare(langues.at(i).toLower())==0)
        {
            this->languesDisplay.append(langues.at(i));
        }
    }
    for(int i=0; i<langues.size();i++){
        if(settings->value("langue").toString().compare(langues.at(i).toLower())!=0){
            this->languesDisplay.append(langues.at(i));
        }
    }
    //this->setFixedHeight(300);
    //this->setFixedWidth(500);
    initAllTab();
    createConnection();
    this->translator = translator;
}


void MenuSettings::initAllTab(){

    initTabGeneral();

    initTabWindow();

    initTabShortcut();
    buttonApply = new QPushButton();
    buttonQuit = new QPushButton();
    layoutSettings->addWidget(tabWidget);
    layoutButton = new QHBoxLayout();
    layoutButton->addWidget(buttonQuit);
    layoutButton->addWidget(buttonApply);
    layoutSettings->addLayout(layoutButton);
    setAllText();
}

void MenuSettings::initTabGeneral(){
    tabWidget->addTab(tabGeneral, tr("Générale"));
    langueChoice = new QComboBox();
    langueChoice->addItems(languesDisplay);
    layoutGeneral->addWidget(labelLangue, 0);
    layoutGeneral->addWidget(langueChoice, 1);
    tabGeneral->setLayout(layoutGeneral);

}

void MenuSettings::initTabWindow(){
    tabWidget->addTab(tabWindow, tr("Fenêtre"));
    boxForSizeSettings = new QGroupBox;
    layoutQRadioButton = new QVBoxLayout;
    layoutQRadioButton->addWidget(buttonForDefault);
    layoutQRadioButton->addWidget(buttonForMaximize);
    layoutQRadioButton->addWidget(buttonForFullscreen);
    layoutQRadioButton->addWidget(buttonForPersonalize);
    boxForSizeSettings->setLayout(layoutQRadioButton);

    boxForPersonalizationLength = new QGroupBox;
    boxForPersonalizationLength->setTitle(tr("Personnalisation"));
    QHBoxLayout *layoutHBoxHeight = new QHBoxLayout;
    editForHeight = new QLineEdit;
    layoutHBoxHeight->addWidget(lblForHeight);
    layoutHBoxHeight->addWidget(editForHeight);


    QHBoxLayout *layoutHBoxWidth = new QHBoxLayout;
    editForWidth = new QLineEdit;
    layoutHBoxWidth->addWidget(lblForWidth);
    layoutHBoxWidth->addWidget(editForWidth);

    layoutPersonalization = new QVBoxLayout;
    layoutPersonalization->addLayout(layoutHBoxHeight);
    layoutPersonalization->addLayout(layoutHBoxWidth);
    boxForPersonalizationLength->setLayout(layoutPersonalization);

    //std::cout << settings->value("size").toString().contains("default") << std::endl;
    if(settings->value("size").toString().contains("default")){
        buttonForDefault->setChecked(true);
        boxForPersonalizationLength->setDisabled(true);
    }
    else if(settings->value("size").toString().contains("maximised")){
        buttonForMaximize->setChecked(true);
        boxForPersonalizationLength->setDisabled(true);
    }else if(settings->value("size").toString().contains("fullscreen")){
        buttonForFullscreen->setChecked(true);
        boxForPersonalizationLength->setDisabled(true);
    }else if(settings->value("size").toString().contains("personalize")){
        buttonForPersonalize->setChecked(true);
        std::cout << settings->value("size").toString().split(" ")[1].toStdString() << std::endl;
        editForHeight->setText(settings->value("size").toString().split(" ")[1]);
        editForWidth->setText(settings->value("size").toString().split(" ")[2]);
    }

    tabWindow->setLayout(layoutWindow);
    layoutWindow->addWidget(lblInfoSizeWindow);
    layoutWindow->addWidget(boxForSizeSettings);
    layoutWindow->addWidget(boxForPersonalizationLength);
}

void MenuSettings::setAllText(){
    labelLangue->setText(tr("Langues : "));
    tabWidget->setTabText(0, tr("Générale"));
    tabWidget->setTabText(1, tr("Fenêtre"));
    tabWidget->setTabText(2, tr("Raccourcis"));
    buttonApply->setText(tr("Appliquer"));
    buttonQuit->setText(tr("Quitter"));

    lblInfoSizeWindow->setText(tr("Taille de la fenêtre : "));
    buttonForDefault->setText(tr("Par défaut"));
    buttonForMaximize->setText(tr("Maximisée"));
    buttonForFullscreen->setText(tr("Plein Ecran"));
    buttonForPersonalize->setText(tr("Personnalisée"));

    lblForHeight->setText(tr("Hauteur"));
    lblForWidth->setText(tr("Largeur"));
}

void MenuSettings::initTabShortcut(){
    tabWidget->addTab(tabShortcut, tr("Raccourcis"));
    scrollAreaShortcut->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollAreaShortcut->setWidgetResizable(true);
    scrollAreaShortcut->setFixedHeight(200);
    tabShortcut->setFixedWidth(300);
    tabShortcut->setLayout(layoutShortcut);
    layoutShortcut->addWidget(scrollAreaShortcut);

    widgetScroll = new QWidget();
    scrollAreaShortcut->setWidget(widgetScroll);

    QLabel *lblNamePartShortcutFile = new QLabel();
    lblNamePartShortcutFile->setText(tr("Fichier"));
    //widgetScroll->setLayout(layoutScroll);
    layoutScroll = new QVBoxLayout(widgetScroll);
    layoutScroll->addWidget(lblNamePartShortcutFile);

    loadShortcut(0);

    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layoutScroll->addWidget(line);

    loadShortcut(1);

    line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layoutScroll->addWidget(line);

    loadShortcut(2);

    line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layoutScroll->addWidget(line);

    loadShortcut(3);


}

void MenuSettings::loadShortcut(int indOfThePartOfTheShortcut){
    for(int i=0; i<listOfListQAction->at(indOfThePartOfTheShortcut)->size();i++){
        QHBoxLayout *layoutBox = new QHBoxLayout;
        QLabel *lblShortcutName = new QLabel(listOfListQAction->at(indOfThePartOfTheShortcut)->at(i)->text());
        if(lblShortcutName->text().at(0) == '&'){
            lblShortcutName->setText(lblShortcutName->text().remove(0, 1));
        }
        lblShortcutName->setFixedWidth(WIDTHLABELSHORTCUT);
        layoutBox->addWidget(lblShortcutName);
        QLabel *labelShortcut = new QLabel(listOfListQAction->at(indOfThePartOfTheShortcut)->at(i)->shortcut().toString());
        labelShortcut->setFixedWidth(WIDTHLABELSHORTCUT/2);
        layoutBox->addWidget(labelShortcut);
        labelShortcut->move(WIDTHLABELSHORTCUT+1, 0);
        //layoutScroll->addWidget(new QLabel(listOfListQAction->at(0)->at(i)->text()));
        layoutScroll->addLayout(layoutBox);
    }
}

void MenuSettings::changeLanguage(){
    translator->load(":/"+langueChoice->currentText().toLower()+".qm");
}

void MenuSettings::createConnection(){
    connect(buttonQuit, &QPushButton::clicked, this, &MenuSettings::verifyClose);
    connect(buttonApply, &QPushButton::clicked, this, &MenuSettings::applyConfig);
    connect(langueChoice, &QComboBox::currentTextChanged, this, &MenuSettings::changeLanguage);
    connect(buttonForDefault, &QRadioButton::clicked, this, [this]{boxForPersonalizationLength->setDisabled(true);});
    connect(buttonForMaximize, &QRadioButton::clicked, this, [this]{boxForPersonalizationLength->setDisabled(true);});
    connect(buttonForFullscreen, &QRadioButton::clicked, this, [this]{boxForPersonalizationLength->setDisabled(true);});
    connect(buttonForPersonalize, &QRadioButton::clicked, this, [this]{boxForPersonalizationLength->setEnabled(true);});
}

void MenuSettings::undoLanguage(){
    translator->load(":/"+settings->value("langue").toString().toLower()+".qm");
}

void MenuSettings::changeEvent(QEvent *event){
    if(event->type() == QEvent::LanguageChange){
        setAllText();
    }
}

bool MenuSettings::verifyLanguage(){
    return langueChoice->currentText().toLower().compare(settings->value("langue").toString().toLower())==0;
}

void MenuSettings::verifyClose(){
    if(!verifyLanguage()){
        int undoChanges = QMessageBox::question(this, tr("Fermer les settings"),
                                                tr("Voulez-vous vraiment quitter sans appliquer les modifications ?"),
                                                QMessageBox::Yes, QMessageBox::No);
        switch(undoChanges){
            case QMessageBox::Yes:{
                undoLanguage();
                close();
                break;
            }
            case QMessageBox::No:{

                break;
            }
        }
    }else{
        close();
    }
}

void MenuSettings::applyConfig(){
    settings->setValue("langue", langueChoice->currentText().toLower());

    if(buttonForDefault->isChecked()){
        settings->setValue("size","default");
    }
    else if(buttonForMaximize->isChecked()){
        settings->setValue("size","maximised");
    }
    else if(buttonForFullscreen->isChecked()){
        settings->setValue("size","fullscreen");
    }
    else if(buttonForPersonalize->isChecked()){
        if(editForHeight->text().compare("") == 0 || editForWidth->text().compare("") == 0){
            //Test false.
        }else{
            settings->setValue("size","personalize " + editForHeight->text() + " " + editForWidth->text());
            //std::cout << "personalize " << hauteur->text().toStdString() << " " << largeur->text().toStdString() << std::endl;
        }

   }
//    LoadSettings *loadSettings = new LoadSettings(((QMainWindow*)this->parent()), translator);
//    loadSettings->loadAllConfig();
    //settings.setValue("size","personalize " + hauteur->text() + " " + largeur->text());
    close();
}



















