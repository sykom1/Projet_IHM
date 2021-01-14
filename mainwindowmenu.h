#ifndef MAINWINDOWMENU_H
#define MAINWINDOWMENU_H

#include "ui_mainwindowmenu.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QScrollArea>
#include <QLabel>
#include <iostream>

class mainWindowMenu : public QMainWindow, private Ui::mainWindowMenu
{
    Q_OBJECT

public:
    mainWindowMenu(QWidget *parent = nullptr);
    ~mainWindowMenu();

private slots:
    void openNewFile();

private:
    QScrollArea *scrollAreaForImage;
    QLabel *labelForImage;
};
#endif // MAINWINDOWMENU_H
