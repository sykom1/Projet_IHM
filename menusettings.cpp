#include "menusettings.h"

MenuSettings::MenuSettings(QStringList langues, QWidget *parent) : QWidget(parent)
{
    layoutSettings = new QVBoxLayout();
    this->setLayout(layoutSettings);
    this->langues = langues;
    //this->setFixedHeight(300);
    //this->setFixedWidth(500);
    initAllTab();
}


void MenuSettings::initAllTab(){
    tabWidget = new QTabWidget;

    initTabGeneral();

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
    langueChoice->addItems(langues);
    layoutGeneral->addWidget(labelLangue, 0);
    layoutGeneral->addWidget(langueChoice, 1);
    tabGeneral->setLayout(layoutGeneral);

}

void MenuSettings::setAllText(){
    labelLangue->setText(tr("Langues : "));
    tabWidget->setTabText(0, tr("Générale"));
    tabWidget->setTabText(1, tr("Raccourcis"));
    buttonApply->setText(tr("Appliquer"));
    buttonQuit->setText(tr("Quitter"));
}

void MenuSettings::initTabShortcut(){
    tabShortcut = new QWidget();
    tabWidget->addTab(tabShortcut, tr("Raccourcis"));
}
