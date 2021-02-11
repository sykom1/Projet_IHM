#include "imageforchange.h"

ImageForChange::ImageForChange(QAction *actionUndo, QAction *actionRedo,DisplayContains *displayContains)
{
    actualImg = QImage();
    initImg = QImage();
    reduceImg = QImage();
    this->displayContains = displayContains;
    this->actionUndo = actionUndo;
    this->actionRedo = actionRedo;
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(false);

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
    initImg = actualImg;
}

void ImageForChange::changeActualImg(QImage newImg){
    actualImg = newImg;
    ajouter();

    if(isNext()){
        actionRedo->setEnabled(true);
        buttonRedo->setEnabled(true);
    }else{
        actionRedo->setEnabled(false);
        buttonRedo->setEnabled(false);
    }
    if(isPrevious()){
        actionUndo->setEnabled(true);
        buttonUndo->setEnabled(true);
    }else{
        actionUndo->setEnabled(false);
        buttonUndo->setEnabled(false);
    }
}

void ImageForChange::changeActualReduceImage(){
    reduceImg = actualImg;
}

void ImageForChange::initActualImg(){
    actualImg = initImg.copy();
    ajouter();
    if(isNext()){
        actionRedo->setEnabled(true);
        buttonRedo->setEnabled(true);
    }else{
        actionRedo->setEnabled(false);
        buttonRedo->setEnabled(false);
    }
    if(isPrevious()){
        actionUndo->setEnabled(true);
        buttonUndo->setEnabled(true);
    }else{
        actionUndo->setEnabled(false);
        buttonUndo->setEnabled(false);
    }
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


QImage ImageForChange::getFiltersImg(){
    return filterImg;
}

void ImageForChange::setFilterImg(QImage image){
    filterImg = image;
}

void ImageForChange::setButtonUndoRedo(QPushButton *undoButton, QPushButton *redoButton){
    this->buttonUndo = undoButton;
    this->buttonRedo = redoButton;
}

void ImageForChange::ajouter(){

       if(idarrayImage < SIZEARRAY-1){
           arrayImage[++idarrayImage] = actualImg;
           idLimite = idarrayImage;
           arrayPosImage[idarrayImage] = QPoint(displayContains->getScrollArea()->x(),displayContains->getScrollArea()->y());

           std::cout << arrayPosImage[idarrayImage].x()  <<" | " <<  arrayPosImage[idarrayImage].y() << std::endl;

       }else{
           decaler();
           arrayImage[SIZEARRAY-1] = actualImg;
           arrayPosImage[SIZEARRAY-1] = QPoint(displayContains->getScrollArea()->x(),displayContains->getScrollArea()->y());
       }

}

void ImageForChange::decaler(){
    for(int i = 1;i<SIZEARRAY;i++){
        arrayImage[i-1] = arrayImage[i];
        arrayPosImage[i-1] = arrayPosImage[i];
    }

}

void ImageForChange::retourArriere(){
   if(isPrevious()){
       actualImg = arrayImage[--idarrayImage];
       displayContains->refreshImage(actualImg, arrayPosImage[idarrayImage].x(), arrayPosImage[idarrayImage].y());


   }
   if(isNext()){
       actionRedo->setEnabled(true);
       buttonRedo->setEnabled(true);
   }else{
       actionRedo->setEnabled(false);
       buttonRedo->setEnabled(false);
   }
   if(isPrevious()){
       actionUndo->setEnabled(true);
       buttonUndo->setEnabled(true);
   }else{
       actionUndo->setEnabled(false);
       buttonUndo->setEnabled(false);
   }

}

void ImageForChange::retourAvant(){
    if(isNext()){
        actualImg = arrayImage[++idarrayImage];
        displayContains->refreshImage(actualImg, arrayPosImage[idarrayImage].x(), arrayPosImage[idarrayImage].y());

    }
    if(isNext()){
        actionRedo->setEnabled(true);
        buttonRedo->setEnabled(true);
    }else{
        actionRedo->setEnabled(false);
        buttonRedo->setEnabled(false);
    }
    if(isPrevious()){
        actionUndo->setEnabled(true);
        buttonUndo->setEnabled(true);
    }else{
        actionUndo->setEnabled(false);
        buttonUndo->setEnabled(false);
    }
}

bool ImageForChange::isNext(){

    return idarrayImage < idLimite;
}

bool ImageForChange::isPrevious(){

    return idarrayImage > 0;
}

void ImageForChange::wheelEvent(QWheelEvent *wheelEvent)
{

    if(!this->getActualImg().isNull()){
        QImage img = this->getActualImg();
        int width = this->getActualImg().width();
        int height = this->getActualImg().height();
        if(QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier)){
            if(wheelEvent->delta()>0){
                img = img.scaled(width*1.15,height*1.15,Qt::IgnoreAspectRatio,Qt::FastTransformation);
                this->changeActualImg(img);
                displayContains->refreshImage(this->getActualImg(), displayContains->getScrollArea()->x(), displayContains->getScrollArea()->y());
            }
            else{
                img = img.scaled(width*0.85,height*0.85,Qt::IgnoreAspectRatio,Qt::FastTransformation);
                this->changeActualImg(img);
                displayContains->refreshImage(this->getActualImg(), displayContains->getScrollArea()->x(), displayContains->getScrollArea()->y());
            }
        }
        else{
            std::cout << "control pas appuyé" << std::endl;
        }
    }
    else{
        std::cout << "imùage fermée" << std::endl;
    }
}












