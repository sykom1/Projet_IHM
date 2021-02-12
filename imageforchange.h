#ifndef IMAGEFORCHANGE_H
#define IMAGEFORCHANGE_H

#include <QImage>
#include <QImageReader>
#include <QAction>
#include <iostream>
#include <QPushButton>
#include <QWidget>
#include <QtWidgets>
#include "resizepicture.h"
#include "displaycontains.h"
#define SIZEARRAY 15

class ImageForChange
{
public:
    ImageForChange(QAction *buttonUndo, QAction *buttonRedo,DisplayContains *displayContains);
    void initImgWithPath(QString pathImg);
    bool isNull();
    void changeSizeReduceImg();
    QImage getActualImg();
    QImage getInitImg();
    QImage getFiltersImg();
    QImage getReduceImg();
    void setFilterImg(QImage image);
    void ajouter();
    void decaler();
    void retourArriere();
    void retourAvant();
    bool isNext();
    bool isPrevious();
    void saveImg(QString pathNameSave);
    void changeActualImg(QImage newImg);
    void initActualImg();
    void changeActualReduceImage();
    void setButtonUndoRedo(QPushButton *undoButton, QPushButton *redoButton);

private:
    int idarrayImage = -1;
    int idLimite = -1;
    QImage arrayImage[SIZEARRAY];
    QPoint arrayPosImage[SIZEARRAY];
    DisplayContains *displayContains;
    QImage initImg;
    QImage actualImg;
    QImage filterImg;
    QImage reduceImg;
    QAction *actionUndo;
    QAction *actionRedo;
    QPushButton *buttonUndo = nullptr;
    QPushButton *buttonRedo = nullptr;
};

#endif // IMAGEFORCHANGE_H
