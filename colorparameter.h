#ifndef COLORPARAMETER_H
#define COLORPARAMETER_H

#include "ui_colorparameter.h"
#include "mainwindowmenu.h"
#include "filters.h"

#include <QObject>
#include <QDialog>
#include <QDebug>
#include <QColor>
#include <QPalette>

class colorParameter : public QDialog, private Ui::colorparameter
{
    Q_OBJECT

private :
    mainWindowMenu *mainWindMen;
public:
    explicit colorParameter(mainWindowMenu *mainWindMen, QWidget *parent = nullptr);
    static void windowOpen(int r,int g, int b);

protected slots:
        void colorChanged();

private slots:
    void on_redValueLabel_windowIconTextChanged(const QString &iconText);
};

#endif // COLORPARAMETER_H
