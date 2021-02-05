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

class InitConfig : public QWidget, private Ui::InitConfig
{
    Q_OBJECT

public:
    explicit InitConfig(QStringList langues,QWidget *parent = nullptr);
    void runAllEvent();


public slots:
    void setWindowSize();
    void setLanguage();
    void setPathImage();
    void validConfig();
    void verifConfig();

private :
    QString lang = QString();
    QString pathDirImage = QString();
    bool languesReady = false;
    bool windowSizeReady = false;
    bool pathReady = false;
    QButtonGroup group;

};



#endif // INITCONFIG_H
