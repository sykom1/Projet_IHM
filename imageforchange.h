#ifndef IMAGEFORCHANGE_H
#define IMAGEFORCHANGE_H

#include <QImage>
#include <QImageReader>
#include "resizepicture.h"
#include <vector>
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
    void ajouter(QImage newImg);
    void decaler();
    void retourArriere();
    bool isNext();
    bool isPrevious();
    void saveImg(QString pathNameSave);
    void changeActualImg(QImage newImg);
    void initActualImg();

    void updateList(Element *e);

private:
    int idarrayImage = 0;
    const int sizeArrayImage = 4;
    std::vector<QImage> arrayImage;
    QImage initImg;
    QImage actualImg;
    QImage reduceImg;
};

#endif // IMAGEFORCHANGE_H
