#ifndef MAINWINDOWMENU_H
#define MAINWINDOWMENU_H

#include "ui_mainwindowmenu.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QScrollArea>
#include <QLabel>
#include <iostream>
#include <QLayout>
#include "formsandcrop.h"

class mainWindowMenu : public QMainWindow, private Ui::mainWindowMenu
{
    Q_OBJECT

public:
    mainWindowMenu(QWidget *parent = nullptr);
    ~mainWindowMenu();

private slots:
    void openNewFile();
    void closeFile();
    void saveFile();
    void doFilter(QImage img);
    void doResizing(QImage img);
    void doTrim(QImage img,int trimSelect);
    void selectMode(QImage img,int trimSelect);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QScrollArea *scrollAreaForImage;
    QLabel *labelForImage;
    QImage theImg;
    int modState = 1;
    int mode = 0;
    void initSize();
    void setMenuEnabled(bool valueMenuEnabled);
    void addShortCutToAction();
    void runAllEventFromTheMainWindow();
    FormsAndCrop *formAndCrop = nullptr;
};
#endif // MAINWINDOWMENU_H
