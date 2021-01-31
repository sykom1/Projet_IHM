#ifndef COLORPARAMETER_H
#define COLORPARAMETER_H

#include "ui_colorparameter.h"
#include "mainwindowmenu.h"
#include "filters.h"
#include "displaycontains.h"

#include <QObject>
#include <QDialog>
#include <QDebug>
#include <QColor>
#include <QPalette>

class colorParameter : public QDialog, private Ui::colorparameter
{
    Q_OBJECT

public:
    colorParameter();
    colorParameter(QWidget* parent = nullptr);
    colorParameter(ImageForChange* imgForChange, DisplayContains* dispCont, QWidget *parent = nullptr);
    static void windowOpen(int r,int g, int b);

protected slots:
        void colorChanged();

private slots:
        void on_redValueLabel_windowIconTextChanged(const QString &iconText);

private :
        ImageForChange *imgForChange;
        DisplayContains *displayContains;


};

#endif // COLORPARAMETER_H
