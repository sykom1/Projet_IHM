#ifndef BARBUTTONRETOUCH_H
#define BARBUTTONRETOUCH_H

#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <iostream>
#include <QMainWindow>
#include <QLayout>
#include "formsandcrop.h"
#include "imageforchange.h"
#include "displaycontains.h"
#define WIDTHVAL 40
#define HEIGHTVAL 25

class BarButtonRetouch : public QWidget
{
    Q_OBJECT
public:
    explicit BarButtonRetouch(ImageForChange *imageForChange, DisplayContains *displayContains,
                              QWidget *parent = nullptr);
    FormsAndCrop* getFormsAndCrop();

private slots:
    void squareSelectButton();
    void circleSelectButton();
    void doTrim();
    void deleteSelec();

private:
    enum Selection { Square = 1, Circle};
    ImageForChange *imageForChange = nullptr;
    DisplayContains *displayContains = nullptr;
    QPushButton *selectSquare;
    QPushButton *selectCircle;
    QPushButton *crop;
    QPushButton *deleteSelectionButton;
    bool selectSquareIsDown = false;
    bool selectCircleIsDown = false;
    FormsAndCrop *formsAndCrop = nullptr;
    int modState;
    void initAllButton();
    void runAllEvent();
    void upAllButton();
    void selectMode(Selection select);
    void disableAllButton();
    void enableAllButton();
};

#endif // BARBUTTONRETOUCH_H
