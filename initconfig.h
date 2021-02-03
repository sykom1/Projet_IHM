#ifndef INITCONFIG_H
#define INITCONFIG_H

#include "ui_initconfig.h"
#include <QLabel>
#include<QLineEdit>


class InitConfig : public QWidget, private Ui::InitConfig
{
    Q_OBJECT

public:
    explicit InitConfig(QWidget *parent = nullptr);
    void runAllEvent();


private :

};



#endif // INITCONFIG_H
