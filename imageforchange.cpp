#include "imageforchange.h"

ImageForChange::ImageForChange()
{
    actualImg = QImage();
    initImg = QImage();
    reduceImg = QImage();
}

void ImageForChange::initImgWithPath(QString pathImg){
    QImageReader readerImage(pathImg);
    QImageReader readerImageInit(pathImg);
    QImageReader readerReduceImage(pathImg);
    readerImage.setAutoTransform(true);

    actualImg = readerImage.read();
    initImg = readerImageInit.read();
    reduceImg = readerReduceImage.read();
}

bool ImageForChange::isNull(){
    return actualImg.isNull() || initImg.isNull() || reduceImg.isNull();
}

void ImageForChange::changeSizeReduceImg(){
    resizePicture *picture = new resizePicture();
    reduceImg = picture->resize(reduceImg, reduceImg.width()/3, reduceImg.height()/3);
}

void ImageForChange::saveImg(QString pathNameSave){
    actualImg.save(pathNameSave);
}

void ImageForChange::changeActualImg(QImage newImg){
    actualImg = newImg;
}

void ImageForChange::avancer(Element *e){
    actualImg = e->precedent->image;
}

void ImageForChange::reculer(Element *e){
    actualImg = e->suivant->image;
}

void ImageForChange::initActualImg(){
    actualImg = initImg.copy();
}

QImage ImageForChange::getActualImg(){
    return actualImg;
}

QImage ImageForChange::getInitImg(){
    return initImg;
}

QImage ImageForChange::getReduceImg(){
    return reduceImg;
}












