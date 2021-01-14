#ifndef MAINWINDOWMENU_H
#define MAINWINDOWMENU_H

#include "ui_mainwindowmenu.h"

#include <QMainWindow>

class mainWindowMenu : public QMainWindow, private Ui::mainWindowMenu
{
    Q_OBJECT

public:
    mainWindowMenu(QWidget *parent = nullptr);
    ~mainWindowMenu();

private slots:
    void createNewFile();
};
#endif // MAINWINDOWMENU_H
