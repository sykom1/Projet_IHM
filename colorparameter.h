#ifndef COLORPARAMETER_H
#define COLORPARAMETER_H

#include "ui_colorparameter.h"
#include "mainwindowmenu.h"

class colorParameter : public QDialog, private Ui::colorparameter
{
    Q_OBJECT

public:
    explicit colorParameter(QWidget *parent = nullptr);
    static void windowOpen(int r,int g, int b);

private:
};

#endif // COLORPARAMETER_H
