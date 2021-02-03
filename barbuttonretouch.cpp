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
    selectSquare->setIcon(QIcon(":/Resources/square.png"));


    selectCircle = new QPushButton(this);
    selectCircle->setFixedWidth(WIDTHVAL);
    selectCircle->setFixedHeight(HEIGHTVAL);
    selectCircle->move(0, (heightVar++)*HEIGHTVAL);
    selectCircle->setIcon(QIcon(":/Resources/rond.png"));

    selectDraw = new QPushButton(this);
    selectDraw->setFixedWidth(WIDTHVAL);
    selectDraw->setFixedHeight(HEIGHTVAL);
    selectDraw->move(0, (heightVar++)*HEIGHTVAL);
    selectDraw->setIcon(QIcon(":/Resources/crayon.png"));

    crop = new QPushButton(this);
    crop->setFixedWidth(WIDTHVAL);
    crop->setFixedHeight(HEIGHTVAL);
    crop->move(0, (heightVar++)*HEIGHTVAL);
    crop->setIcon(QIcon(":/Resources/rognage.png"));

    deleteSelectionButton = new QPushButton(this);
    deleteSelectionButton->setFixedWidth(WIDTHVAL);
    deleteSelectionButton->setFixedHeight(HEIGHTVAL);
    deleteSelectionButton->move(0, (heightVar++)*HEIGHTVAL);
    deleteSelectionButton->setIcon(QIcon(":/Resources/del.png"));
}

void BarButtonRetouch::runAllEvent(){
    connect(selectSquare, &QPushButton::clicked, this, &BarButtonRetouch::squareSelectButton);
    connect(selectCircle, &QPushButton::clicked, this, &BarButtonRetouch::circleSelectButton);
    connect(selectDraw, &QPushButton::clicked, this, &BarButtonRetouch::drawSelectButton);
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

void BarButtonRetouch::drawSelectButton(){
    if(!selectDrawIsDown){
        upAllButton();
        selectDraw->setDown(true);
        selectDrawIsDown = true;
        selectMode(Draw);
        disableAllButton();
    }
    else{
        disableAllButton();
        selectDraw->setDown(false);
        selectDrawIsDown = false;
        if(formsAndCrop != nullptr){
            ((QMainWindow *)this->parent())->layout()->removeWidget(formsAndCrop);
            formsAndCrop->close();
            formsAndCrop->clearImage();
            if(colorWindow != nullptr){
                colorWindow->close();
                //colorWindow = nullptr;
            }
        }
        formsAndCrop = nullptr;
    }
}

void BarButtonRetouch::upAllButton(){
    selectSquareIsDown = false;
    selectCircleIsDown = false;
    selectDrawIsDown = false;


    selectSquare->setDown(false);
    selectCircle->setDown(false);
    selectDraw->setDown(false);

}

void BarButtonRetouch::selectMode(Selection select){
    if(formsAndCrop != nullptr){
        ((QMainWindow*)this->parent())->layout()->removeWidget(formsAndCrop);
        formsAndCrop->close();
        formsAndCrop->clearImage();
    }

    modState = select;
    std::cout << displayContains->getScrollArea()->horizontalScrollBar()->isVisible() << std::endl;
    int heightForms = displayContains->getScrollArea()->height();
    int widthForms = displayContains->getScrollArea()->width();
    if(displayContains->getScrollArea()->horizontalScrollBar()->isVisible())
        heightForms-=displayContains->getScrollArea()->horizontalScrollBar()->height();
    if(displayContains->getScrollArea()->verticalScrollBar()->isVisible())
        widthForms-=displayContains->getScrollArea()->verticalScrollBar()->width();
    formsAndCrop = new FormsAndCrop(displayContains->x(),
                                    displayContains->y(),
                                    displayContains->getScrollArea()->height()-displayContains->getScrollArea()->horizontalScrollBar()->height(),
                                    displayContains->getScrollArea()->width()-displayContains->getScrollArea()->verticalScrollBar()->width(),select,
                                    displayContains->getScrollArea(), displayContains, imageForChange);
    formsAndCrop->setFixedHeight(heightForms);
    formsAndCrop->setFixedWidth(widthForms);
    formsAndCrop->move(displayContains->getScrollArea()->x(), displayContains->getScrollArea()->y()+displayContains->y());
    ((QMainWindow*)this->parent())->layout()->addWidget(formsAndCrop);
    if(modState == Draw){
        colorMenu();
    }
    raise();
}

void BarButtonRetouch::recreateFormsAndCrop(){
    if(formsAndCrop!=nullptr){
        ((QMainWindow*)this->parent())->layout()->removeWidget(formsAndCrop);
        formsAndCrop->close();
        formsAndCrop->clearImage();
        formsAndCrop->initCrop();
        formsAndCrop = nullptr;

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
    }else{
        formsAndCrop = new FormsAndCrop(displayContains->x(),
                                        displayContains->y(),
                                        displayContains->getScrollArea()->height()-displayContains->getScrollArea()->horizontalScrollBar()->height(),
                                        displayContains->getScrollArea()->width()-displayContains->getScrollArea()->verticalScrollBar()->width(),modState,
                                        displayContains->getScrollArea(), displayContains, imageForChange);
        formsAndCrop->initCrop();
        formsAndCrop->clearImage();
        formsAndCrop->close();
        formsAndCrop=nullptr;
    }
}

void BarButtonRetouch::doTrim(){
    if(formsAndCrop->x != formsAndCrop->y != formsAndCrop->firstP != formsAndCrop->lastP){
        formsAndCrop->doTrim(imageForChange->getActualImg(), modState, displayContains->getLabelForImage());
        //displayContains->getScrollArea()->move(formsAndCrop->xCrop, formsAndCrop->yCrop);
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
        displayContains->refreshImage(img, 0, 0);
        imageForChange->changeActualImg(img);
        displayContains->moveScrollArea(formsAndCrop->xCrop, formsAndCrop->yCrop);
        displayContains->changeSizeOfScrollBar(((QMainWindow*)this->parent())->width(), ((QMainWindow*)this->parent())->height());

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

void BarButtonRetouch::colorMenu(){
    if(colorWindow==nullptr){
        std::cout << "aaaé" << std::endl;
        colorWindow = new choseColor(((QMainWindow*)this->parent()));
    }
    if(colorWindow->close()){
        //colorWindow = new choseColor(((QMainWindow*)this->parent()));
        moveColorWindow();
        colorWindow->show();
    }else{
        colorWindow->close();
        //colorWindow->setParent(nullptr);
        //colorWindow = nullptr;
    }
}

void BarButtonRetouch::moveColorWindow(){
    if(colorWindow != nullptr){
        QSize valueSize = ((QMainWindow*)this->parent())->size();
        QPoint p = ((QMainWindow*)this->parent())->mapToGlobal(QPoint(valueSize.width()-5, valueSize.height()-40)) -
                QPoint(colorWindow->size().width(), colorWindow->size().height());
        colorWindow->move(p);
    }
}
























