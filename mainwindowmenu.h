#ifndef MAINWINDOWMENU_H
#define MAINWINDOWMENU_H

#include "ui_mainwindowmenu.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include <QPainterPath>
#include <QLayout>
#include <QVector>
#include <cmath>
#include <string>
#include <iostream>
#include "formsandcrop.h"
#include "resizepicture.h"
#include "displaycontains.h"
#include "imageforchange.h"
#include "chosecolor.h"
#include "barbuttonretouch.h"
#include "colorparameter.h"
#include "loadsettings.h"
#include "menusettings.h"


class mainWindowMenu : public QMainWindow, private Ui::mainWindowMenu
{
    Q_OBJECT

public:
    mainWindowMenu(QTranslator *t, QStringList langues, QWidget *parent = nullptr);
    ~mainWindowMenu();
    static void printPixels(ImageForChange *image);
    ImageForChange* getImageForChange();
    DisplayContains *getDisplayContains();
    QTranslator* getTranslation();

private slots:
    void closeEvent(QCloseEvent *event);
    void moveEvent(QMoveEvent *event);
    void openNewFile();
    void closeFile();
    void saveFileOn();
    void saveFile();
    void zoom();
    void dezoom();
    void doResizing(QImage img, int x, int y);
    void doResizing(QImage img);
    void doTrim(QImage img,int trimSelect);
    void selectMode(QImage img,int trimSelect);
    void deleteSelec(QImage img,int trimSelect);
    void updateLanguage(const QString language);
    void resizeClicked(QLineEdit *lineEdit, QLineEdit *lineEdit2,QDialog *dialog,QImage img);
    void openColorParameter();
    void openSettings();


protected:
    void resizeEvent(QResizeEvent *event);
    void changeEvent(QEvent *event);
    void wheelEvent(QWheelEvent *wheelEvent);

private:
    QVector<QVector<QAction*>*> *listofListQAction = new QVector<QVector<QAction*>*>;
    QVector<QAction*> *listQActionFile = new QVector<QAction*>;
    QVector<QAction*> *listQActionRetouch = new QVector<QAction*>;
    QVector<QAction*> *listQActionEdition = new QVector<QAction*>;
    QVector<QAction*> *listQActionSelection = new QVector<QAction*>;
    QStringList langues;
    LoadSettings *loadSettings = nullptr;
    QString pathForFileImg = nullptr;
    MenuSettings *menuSettings = nullptr;
    DisplayContains *displayContains = nullptr;
    ImageForChange *imageForChange = nullptr;
    QLabel *name = new QLabel();
    QLabel *labelHauteur = new QLabel();
    QLabel *labelLargeur = new QLabel();
    int mode = 0;
    QString pathImg = nullptr;
    std::string nameImage = "";
    QTranslator *translator;
    void initSize();
    void setMenuEnabled(bool valueMenuEnabled);
    void addShortCutToAction();
    void runAllEventFromTheMainWindow();
    QDialog dialog;
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QLineEdit *lineEdit2 = new QLineEdit(&dialog);
    bool isOpen;
    choseColor *colorWindow = new choseColor(this);
    BarButtonRetouch *barButtonRetouch = nullptr;
    void initLogo();
    void fillListQAction();

};
#endif // MAINWINDOWMENU_H
