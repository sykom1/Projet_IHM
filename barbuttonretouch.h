#ifndef BARBUTTONRETOUCH_H
#define BARBUTTONRETOUCH_H

#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <iostream>
#include <QMainWindow>
#include <QLayout>
#include <QResource>
#include "formsandcrop.h"
#include "imageforchange.h"
#include "displaycontains.h"
#include "chosecolor.h"
#define WIDTHVAL 40
#define HEIGHTVAL 25

class BarButtonRetouch : public QWidget
{
    Q_OBJECT

public:
    explicit BarButtonRetouch(ImageForChange *imageForChange, DisplayContains *displayContains,
                              QWidget *parent = nullptr);
    enum Selection { Square = 1, Circle, Draw};
    FormsAndCrop* getFormsAndCrop();
    void closeFormsAndCrop();
    void selectMode(Selection select);
    void recreateFormsAndCrop();
    int getModState();
    void moveColorWindow();


public slots:
    void doTrim();
    void deleteSelec();
    void squareSelectButton();
    void circleSelectButton();
    void drawSelectButton();
private slots:

private:
    ImageForChange *imageForChange = nullptr;
    DisplayContains *displayContains = nullptr;
    QPushButton *selectSquare;
    QPushButton *selectCircle;
    QPushButton *selectDraw;
    QPushButton *crop;
    QPushButton *deleteSelectionButton;
    bool selectSquareIsDown = false;
    bool selectCircleIsDown = false;
    bool selectDrawIsDown = false;
    FormsAndCrop *formsAndCrop = nullptr;
    choseColor *colorWindow = nullptr;
    int modState;
    void initAllButton();
    void runAllEvent();
    void upAllButton();
    void disableAllButton();
    void enableAllButton();
    void colorMenu();
};

#endif // BARBUTTONRETOUCH_H
