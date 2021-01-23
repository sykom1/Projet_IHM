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
    ajouter();
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
    ajouter();
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

void ImageForChange::ajouter(){
       if(idarrayImage < SIZEARRAY-1){
           arrayImage[++idarrayImage] = actualImg;
           idLimite = idarrayImage;
       }else{
           if(init){
               decaler();
               arrayImage[SIZEARRAY-1] = actualImg;
           }
       }

}

void ImageForChange::decaler(){
    for(int i = 1;i<SIZEARRAY;i++){
        arrayImage[i-1] = arrayImage[i];
    }

}

void ImageForChange::retourArriere(){

   if(isPrevious()){
       actualImg = arrayImage[--idarrayImage];
   }

}

void ImageForChange::retourAvant(){
    if(isNext())
        actualImg = arrayImage[++idarrayImage];
}

bool ImageForChange::isNext(){

    return idarrayImage < idLimite;
}

bool ImageForChange::isPrevious(){

    return idarrayImage > 0;
}












