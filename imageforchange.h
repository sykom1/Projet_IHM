#ifndef IMAGEFORCHANGE_H
#define IMAGEFORCHANGE_H

#include <QImage>
#include <QImageReader>
#include <QAction>
#include "resizepicture.h"
#include <iostream>

#define SIZEARRAY 4

class ImageForChange
{
public:
    ImageForChange(QAction *buttonUndo, QAction *buttonRedo);
    void initImgWithPath(QString pathImg);
    bool isNull();
    void changeSizeReduceImg();
    QImage getActualImg();
    QImage getInitImg();
    QImage getReduceImg();
    void ajouter();
    void decaler();
    void retourArriere();
    void retourAvant();
    bool isNext();
    bool isPrevious();
    void saveImg(QString pathNameSave);
    void changeActualImg(QImage newImg);
    void initActualImg();

private:
    int idarrayImage = -1;
    int idLimite = -1;
    QImage arrayImage[SIZEARRAY];
    QImage initImg;
    QImage actualImg;
    QImage reduceImg;
    QAction *actionUndo;
    QAction *actionRedo;
};

#endif // IMAGEFORCHANGE_H
