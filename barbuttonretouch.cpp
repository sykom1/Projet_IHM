#include "barbuttonretouch.h"

BarButtonRetouch::BarButtonRetouch(ImageForChange *imageForChange, DisplayContains *displayContains,
                                   QWidget *parent) : QWidget(parent)
{
    this->imageForChange = imageForChange;
    this->displayContains = displayContains;
    initAllButton();
    //std::cout << ((QMainWindow*)this->parent())->height() << std::endl;
    this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    this->setFixedWidth(WIDTHVAL);
    this->setFixedHeight(HEIGHTVAL * this->children().size());
    move(0, ((QMainWindow*)this->parent())->height()/2);
    runAllEvent();
    disableAllButton();
}

void BarButtonRetouch::initAllButton(){
    int heightVar = 0;
    selectSquare = new QPushButton(this);
    selectSquare->setFixedWidth(WIDTHVAL);
    selectSquare->setFixedHeight(HEIGHTVAL);
    selectSquare->move(0, (heightVar++)*HEIGHTVAL);
    QPixmap squarePixmap("square.png");
    QIcon squareIcon (squarePixmap);
    selectSquare->setIcon(squareIcon);


    selectCircle = new QPushButton(this);
    selectCircle->setFixedWidth(WIDTHVAL);
    selectCircle->setFixedHeight(HEIGHTVAL);
    selectCircle->move(0, (heightVar++)*HEIGHTVAL);

    crop = new QPushButton(this);
    crop->setFixedWidth(WIDTHVAL);
    crop->setFixedHeight(HEIGHTVAL);
    crop->move(0, (heightVar++)*HEIGHTVAL);

    deleteSelectionButton = new QPushButton(this);
    deleteSelectionButton->setFixedWidth(WIDTHVAL);
    deleteSelectionButton->setFixedHeight(HEIGHTVAL);
    deleteSelectionButton->move(0, (heightVar++)*HEIGHTVAL);
}

void BarButtonRetouch::runAllEvent(){
    connect(selectSquare, &QPushButton::clicked, this, &BarButtonRetouch::squareSelectButton);
    connect(selectCircle, &QPushButton::clicked, this, &BarButtonRetouch::circleSelectButton);
    connect(crop, &QPushButton::clicked, this, &BarButtonRetouch::doTrim);
    connect(deleteSelectionButton, &QPushButton::clicked, this, &BarButtonRetouch::deleteSelec);
}

void BarButtonRetouch::squareSelectButton(){
    if(!selectSquareIsDown){
        upAllButton();
        selectSquare->setDown(true);
        selectSquareIsDown = true;
        selectMode(Square);
        enableAllButton();
    }
    else{
        disableAllButton();
        selectSquare->setDown(false);
        selectSquareIsDown = false;
        if(formsAndCrop != nullptr){
            ((QMainWindow*)this->parent())->layout()->removeWidget(formsAndCrop);
            formsAndCrop->close();
            formsAndCrop->clearImage();
        }
        formsAndCrop = nullptr;
    }
}

void BarButtonRetouch::circleSelectButton(){
    if(!selectCircleIsDown){
        upAllButton();
        selectCircle->setDown(true);
        selectCircleIsDown = true;
        selectMode(Circle);
        enableAllButton();
    }
    else{
        disableAllButton();
        selectCircle->setDown(false);
        selectCircleIsDown = false;
        if(formsAndCrop != nullptr){
            ((QMainWindow*)this->parent())->layout()->removeWidget(formsAndCrop);
            formsAndCrop->close();
            formsAndCrop->clearImage();
        }
        formsAndCrop = nullptr;
    }
}

void BarButtonRetouch::upAllButton(){
    selectSquareIsDown = false;
    selectCircleIsDown = false;


    selectSquare->setDown(false);
    selectCircle->setDown(false);

}

void BarButtonRetouch::selectMode(Selection select){
    if(formsAndCrop != nullptr){
        ((QMainWindow*)this->parent())->layout()->removeWidget(formsAndCrop);
        formsAndCrop->close();
        formsAndCrop->clearImage();
    }

    modState = select;
    formsAndCrop = new FormsAndCrop(displayContains->x(),
                                    displayContains->y(),
                                    displayContains->getScrollArea()->height()-displayContains->getScrollArea()->horizontalScrollBar()->height(),
                                    displayContains->getScrollArea()->width()-displayContains->getScrollArea()->verticalScrollBar()->width(),select,
                                    displayContains->getScrollArea(), displayContains, imageForChange);
    formsAndCrop->setFixedHeight(displayContains->getScrollArea()->height()-displayContains->getScrollArea()->horizontalScrollBar()->height());
    formsAndCrop->setFixedWidth(displayContains->getScrollArea()->width()-displayContains->getScrollArea()->verticalScrollBar()->width());
    ((QMainWindow*)this->parent())->layout()->addWidget(formsAndCrop);
    raise();
}

void BarButtonRetouch::recreateFormsAndCrop(){
    if(formsAndCrop!=nullptr){
        ((QMainWindow*)this->parent())->layout()->removeWidget(formsAndCrop);
        formsAndCrop->close();
        formsAndCrop->clearImage();

        disableAllButton();

        switch(modState){
            case BarButtonRetouch::Square:
                squareSelectButton();
                squareSelectButton();
                break;
            case BarButtonRetouch::Circle:
                circleSelectButton();
                circleSelectButton();
                break;
        }
    }
}

void BarButtonRetouch::doTrim(){
    if(formsAndCrop->x != formsAndCrop->y != formsAndCrop->firstP != formsAndCrop->lastP){
        formsAndCrop->doTrim(imageForChange->getActualImg(), modState, displayContains->getLabelForImage());
    }
    switch(modState){
        case Square :
        {
            upAllButton();
            selectSquare->setDown(true);
            selectSquareIsDown = true;
            selectMode(Square);
            break;
        }
        case Circle:
        {
            upAllButton();
            selectCircle->setDown(true);
            selectCircleIsDown = true;
            selectMode(Circle);
        }
    }
}

void BarButtonRetouch::deleteSelec(){
    if(formsAndCrop->x != formsAndCrop->y != formsAndCrop->firstP != formsAndCrop->lastP){
        QRect rect(formsAndCrop->x, formsAndCrop->y, formsAndCrop->lastP, formsAndCrop->firstP);
        rect = rect.normalized();

        QImage img = imageForChange->getActualImg();
        if(modState == Square){
            for(int i=rect.x(); i<=rect.width() + rect.x(); i++){
                for(int j=rect.y(); j<=rect.height()+rect.y();j++){
                    img.setPixelColor(i, j, Qt::transparent);
                }
            }
        }
        else if(modState == Circle){
            QPainterPath path;
            path.moveTo(rect.x(), rect.y());
            path.addEllipse(rect);

            for(int i=rect.x(); i<=rect.width()+rect.x();i++){
                for(int j = rect.y(); j<=rect.height()+rect.y();j++){
                    QPointF const *newPoint = new QPointF(i, j);
                    if(path.contains(*newPoint)){
                        if(i<imageForChange->getActualImg().width()&&j<imageForChange->getActualImg().height())
                            img.setPixelColor(i, j, Qt::transparent);
                    }
                }
            }
        }
        displayContains->refreshImage(imageForChange->getActualImg(), 0, 0);
        imageForChange->changeActualImg(img);
        displayContains->moveScrollArea(formsAndCrop->xCrop, formsAndCrop->yCrop);

    }
    switch(modState){
        case Square :
        {
            upAllButton();
            selectSquare->setDown(true);
            selectSquareIsDown = true;
            selectMode(Square);
            break;
        }
        case Circle:
        {
            upAllButton();
            selectCircle->setDown(true);
            selectCircleIsDown = true;
            selectMode(Circle);
        }
    }
}

void BarButtonRetouch::disableAllButton(){
    crop->setEnabled(false);
    crop->setVisible(false);

    deleteSelectionButton->setEnabled(false);
    deleteSelectionButton->setVisible(false);
}

void BarButtonRetouch::enableAllButton(){
    crop->setEnabled(true);
    crop->setVisible(true);

    deleteSelectionButton->setEnabled(true);
    deleteSelectionButton->setVisible(true);
}

FormsAndCrop* BarButtonRetouch::getFormsAndCrop(){
    return formsAndCrop;
}

void BarButtonRetouch::closeFormsAndCrop(){
    if(formsAndCrop!=nullptr){
        ((QMainWindow*)this->parent())->layout()->removeWidget(formsAndCrop);
        formsAndCrop->close();
        formsAndCrop->clearImage();
    }
}

int BarButtonRetouch::getModState(){
    return modState;
}
























