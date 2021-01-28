#include "displaycontains.h"

DisplayContains::DisplayContains(QWidget *parent, int heightForScrollArea,
                                 int initX, int initY) : QWidget(parent)
{
    scrollAreaForImage = new QScrollArea(this);
    scrollAreaForImage->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollAreaForImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollAreaForImage->setFrameShape(QFrame::NoFrame);
    labelForImage = new QLabel();
    scrollAreaForImage->setWidget(labelForImage);
    labelForImage->setVisible(false);
    scrollAreaForImage->setVisible(false);
    scrollAreaForImage->move(0, 0);
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

void DisplayContains::refreshImage(QImage img, int x, int y){
    labelForImage->setPixmap(QPixmap::fromImage(img));
    labelForImage->setVisible(true);
    scrollAreaForImage->setVisible(true);
    labelForImage->setFixedHeight(img.height());
    labelForImage->setFixedWidth(img.width());
    scrollAreaForImage->move(x, y);
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
    int newWidth = width;
    if(labelForReduceImage!=nullptr)
        newWidth = width-(labelForReduceImage->width()+10);
    if(newWidth>(labelForImage->width()+scrollAreaForImage->verticalScrollBar()->width()))
        newWidth = labelForImage->width()+scrollAreaForImage->verticalScrollBar()->width();
    scrollAreaForImage->setFixedWidth(newWidth);
    scrollAreaForImage->setFixedHeight(height-scrollAreaForImage->horizontalScrollBar()->height());
    this->setFixedWidth(width);
    this->setFixedHeight(height-scrollAreaForImage->horizontalScrollBar()->height());
    if(labelForImage->height()<height-scrollAreaForImage->horizontalScrollBar()->height())
        this->setFixedHeight(labelForImage->height());
    if(labelForReduceImage!=nullptr)
    {
        labelForReduceImage->move(width-labelForReduceImage->width(), 0);
    }
    scrollAreaForImage->move(0,0);
    this->move(0, heightForScrollArea);
}

int DisplayContains::getWidthScrollBarArea(){
    return scrollAreaForImage->width();
}

int DisplayContains::getHeightScrollBarArea(){
    return scrollAreaForImage->height();
}
















