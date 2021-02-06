#ifndef INITCONFIG_H
#define INITCONFIG_H

#include "ui_initconfig.h"
#include <iostream>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QDir>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSettings>
#include <iostream>
#include <QIntValidator>
#include <QTranslator>
#include "mainwindowmenu.h"

class InitConfig : public QWidget, private Ui::InitConfig
{
    Q_OBJECT

public:
    explicit InitConfig(QTranslator *t,QStringList langues,QWidget *parent = nullptr);
    void runAllEvent();



public slots:
    void setWindowSize();
    void setLanguage();
    void setPathImage();
    void validConfig();
    void verifConfig();
    void changeEvent(QEvent *event);

private :
    QString lang = QString();
    QString pathDirImage = QString();
    bool languesReady = false;
    bool windowSizeReady = false;
    bool pathReady = false;
    QButtonGroup group;
    QTranslator *translator;
    QStringList langues;

};



#endif // INITCONFIG_H
