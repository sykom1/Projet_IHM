#include "menusettings.h"

MenuSettings::MenuSettings(QStringList langues, QWidget *parent) : QWidget(parent)
{
    layoutSettings = new QVBoxLayout();
    this->setLayout(layoutSettings);
    this->langues = langues;
    this->setFixedHeight(300);
    this->setFixedWidth(500);
    initAllTab();
}


void MenuSettings::initAllTab(){
    tabWidget = new QTabWidget;

    initTabGeneral();

    initTabShortcut();
    layoutSettings->addWidget(tabWidget);
}

void MenuSettings::initTabGeneral(){
    tabWidget->addTab(tabGeneral, tr("Générale"));
    langueChoice->addItems(langues);
    layoutGeneral->addWidget(labelLangue);
    layoutGeneral->addWidget(langueChoice);
    tabGeneral->setLayout(layoutGeneral);


    setAllText();
}

void MenuSettings::setAllText(){
    labelLangue->setText(tr("Langues : "));
}

void MenuSettings::initTabShortcut(){
    tabShortcut = new QWidget();
    tabWidget->addTab(tabShortcut, tr("Raccourcis"));
}
