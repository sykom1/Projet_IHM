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
#include <cmath>
#include <QPainterPath>
#include "formsandcrop.h"
#include "resizepicture.h"
#include "displaycontains.h"
typedef struct Element Element;
struct Element
{
    Element *precedent;
    int id;
    QImage image;
    Element *suivant;
};

class mainWindowMenu : public QMainWindow, private Ui::mainWindowMenu
{
    Q_OBJECT



public:
    mainWindowMenu(QTranslator *t, QWidget *parent = nullptr);
    ~mainWindowMenu();

private slots:
    void openNewFile();
    void closeFile();
    void saveFileOn();
    void saveFile();
    void invertPixel();
    void mirroiredH();
    void mirroiredV();
    void doResizing(QImage img, int x, int y);
    void doTrim(QImage img,int trimSelect);
    void selectMode(QImage img,int trimSelect);
    void deleteSelec(QImage img,int trimSelect);
    void updateLanguage(const QString language);
    void initImgDisplay();

protected:
    void resizeEvent(QResizeEvent *event);
    void changeEvent(QEvent *event);

private:
    DisplayContains *displayContains;
    QImage initImg;
    QImage theImg;
    QImage reduceImage;
    FormsAndCrop *formAndCrop = nullptr;
    int modState = 1;
    int mode = 0;
    QString pathImg = nullptr;
    QTranslator *translator;
    void initSize();
    void setMenuEnabled(bool valueMenuEnabled);
    void addShortCutToAction();
    void runAllEventFromTheMainWindow();
    void avancer(Element *e);
    void reculer(Element *e);


};
#endif // MAINWINDOWMENU_H
