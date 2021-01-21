#ifndef IMAGEFORCHANGE_H
#define IMAGEFORCHANGE_H

#include <QImage>
#include <QImageReader>
#include "resizepicture.h"

typedef struct Element Element;
struct Element
{
    Element *precedent;
    int id;
    QImage image;
    Element *suivant;
};

typedef struct List List;
struct List
{
    Element *premier;
};

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
    void saveImg(QString pathNameSave);
    void changeActualImg(QImage newImg);
    void initActualImg();

private:
    QImage initImg;
    QImage actualImg;
    QImage reduceImg;
};

#endif // IMAGEFORCHANGE_H
