#ifndef IMAGEFORCHANGE_H
#define IMAGEFORCHANGE_H

#include <QImage>
#include <QImageReader>
#include "resizepicture.h"
#include <vector>
#include <iostream>

#define SIZEARRAY 4
typedef struct Element Element;

class ImageForChange
{
public:
    ImageForChange();
    void initImgWithPath(QString pathImg);
    void avancer(Element *e);
    void reculer(Element *e);
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
    int idarrayImage = 0;
    QImage arrayImage[SIZEARRAY];
    QImage initImg;
    QImage actualImg;
    QImage reduceImg;
    bool init = false;
};

#endif // IMAGEFORCHANGE_H
