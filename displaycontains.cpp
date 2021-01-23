#include "displaycontains.h"

DisplayContains::DisplayContains(QWidget *parent, int heightForScrollArea,
                                 int initX, int initY) : QWidget(parent)
{
    scrollAreaForImage = new QScrollArea(this);
    scrollAreaForImage->verticalScrollBar()->setFixedWidth(30);
    scrollAreaForImage->horizontalScrollBar()->setFixedHeight(30);
    scrollAreaForImage->setFrameShape(QFrame::NoFrame);
    labelForImage = new QLabel();
    scrollAreaForImage->setWidget(labelForImage);
    labelForImage->setVisible(false);
    scrollAreaForImage->setVisible(false);
    scrollAreaForImage->move(0, heightForScrollArea);
    this->initX = initX;
    this->initY = initY;
    this->heightForScrollArea = heightForScrollArea;
    initSize();
}

void DisplayContains::createNewReducedLabel(QImage reduceImage){
    labelForReduceImage = new QLabel(this);
    labelForReduceImage->setPixmap(QPixmap::fromImage(reduceImage));
}

void DisplayContains::removeParentForReducedLabel(){
    labelForReduceImage->setParent(0);
}

void DisplayContains::setVisibleReducedLabel(bool value){
    labelForReduceImage->setVisible(value);
}

void DisplayContains::setSizeReducedLabel(int height, int width){
    labelForReduceImage->setFixedHeight(height);
    labelForReduceImage->setFixedWidth(width);
}

void DisplayContains::refreshReducedImage(QImage reducedImage){
    labelForReduceImage->setPixmap(QPixmap::fromImage(reducedImage));
    labelForReduceImage->setVisible(true);
    labelForReduceImage->setFixedHeight(reducedImage.height());
    labelForReduceImage->setFixedWidth(reducedImage.width());
}

void DisplayContains::refreshImage(QImage img){
    labelForImage->setPixmap(QPixmap::fromImage(img));
    labelForImage->setVisible(true);
    scrollAreaForImage->setVisible(true);
    labelForImage->setFixedHeight(img.height());
    labelForImage->setFixedWidth(img.width());
    scrollAreaForImage->move(0, heightForScrollArea);
}

bool DisplayContains::reducedLabelIsNull(){
    return labelForReduceImage==nullptr;
}

void DisplayContains::moveReducedLabel(int x, int y){
    labelForReduceImage->move(x, y);
}

void DisplayContains::clearDisplay(){
    labelForImage->clear();
    labelForReduceImage->clear();
    scrollAreaForImage->setWidget(labelForImage);
    initSize();
    scrollAreaForImage->setVisible(false);
}

void DisplayContains::initSize(){
    scrollAreaForImage->setFixedHeight(initY);
    scrollAreaForImage->setFixedWidth(initX);
}

QLabel* DisplayContains::getLabelForImage(){
    return labelForImage;
}

void DisplayContains::moveScrollArea(int x, int y){
    scrollAreaForImage->move(x, y);
}

QScrollArea* DisplayContains::getScrollArea(){
    return scrollAreaForImage;
}

void DisplayContains::changeSizeOfScrollBar(int width, int height){
    scrollAreaForImage->setFixedWidth(width);
    scrollAreaForImage->setFixedHeight(height-scrollAreaForImage->horizontalScrollBar()->height());
    this->setFixedWidth(width);
    this->setFixedHeight(height-scrollAreaForImage->horizontalScrollBar()->height());
}
















