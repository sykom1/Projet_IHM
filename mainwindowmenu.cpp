#include "mainwindowmenu.h"

mainWindowMenu::mainWindowMenu(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    setWindowTitle(tr("Retouche d'Image"));
    scrollAreaForImage = new QScrollArea(this);
    scrollAreaForImage->move(0,menubar->height());
    scrollAreaForImage->verticalScrollBar()->setFixedWidth(30);
    scrollAreaForImage->horizontalScrollBar()->setFixedHeight(30);
    scrollAreaForImage->setFrameShape(QFrame::NoFrame);
    initSize();
    labelForImage = new QLabel();
    scrollAreaForImage->setWidget(labelForImage);
    labelForImage->setVisible(false);
    scrollAreaForImage->setVisible(false);
    runAllEventFromTheMainWindow();
    actionRogner->setEnabled(false);
    menuFiltre->setEnabled(true);
}

void mainWindowMenu::openNewFile(){
    QString pathImage = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Sélectionnez l'image"),
                                                                              QDir::currentPath(), tr("Fichier Image (*.png *.jpg *.bmp)")));
    QImageReader readerImage(pathImage);
    readerImage.setAutoTransform(true);
    theImg = readerImage.read();
    if(!theImg.isNull()){
        refreshImage();
        setMenuEnabled(true);
    }
}

void mainWindowMenu::closeFile(){
    labelForImage->clear();
    scrollAreaForImage->setWidget(labelForImage);
    initSize();
    scrollAreaForImage->setVisible(false);
    setMenuEnabled(false);
}

void mainWindowMenu::saveFile(){
    QString fileNameSave = QFileDialog::getSaveFileName(this,
                                                        tr("Sauvegarder l'image"), "",
                                                        tr("Fichier Image (*.png *.jpg *.bmp)"));
    theImg.save(fileNameSave);
}

void mainWindowMenu::invertPixel(){
    theImg.invertPixels();
    refreshImage();
    std::cout << "rentrer dans la fonction filtre" << std::endl;
}

void mainWindowMenu::mirroiredH(){
    theImg = theImg.mirrored(true,false);
    refreshImage();
}

void mainWindowMenu::mirroiredV(){
    theImg = theImg.mirrored(false,true);
    refreshImage();
}

void mainWindowMenu::doResizing(QImage img, int x,int y){
    resizePicture *picture = new resizePicture();
    theImg = picture->resize(img,x,y);
    refreshImage();
}

void mainWindowMenu::doTrim(QImage img, int trimSelect){
    if(formAndCrop!=nullptr and formAndCrop->x != formAndCrop->y){
        if(trimSelect== 1){
            theImg = img.copy(formAndCrop->x,formAndCrop->y,formAndCrop->lastP,formAndCrop->firstP );
            refreshImage();
            scrollAreaForImage->move(formAndCrop->x, formAndCrop->y);
        }
        else if(trimSelect == 2){

            QPixmap target = QPixmap(size());
            target.fill(Qt::transparent);

            QPixmap p = QPixmap::fromImage(img);
            //p.scaled(200, 200, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);


            QPainter painter (&target);

            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

            QPainterPath path = QPainterPath();
           // path.addRoundedRect(formAndCrop->x,formAndCrop->y, formAndCrop->lastP,formAndCrop->firstP, 50, 50);
            path.addEllipse(formAndCrop->x,formAndCrop->y, formAndCrop->lastP,formAndCrop->firstP);

            painter.setClipPath(path);
            painter.drawPixmap(0, 0, p);
            labelForImage->setPixmap(target);
            theImg = target.toImage();

        }

        formAndCrop->clearImage();
       // scrollAreaForImage->move(formAndCrop->x, formAndCrop->y);
    }


}

void mainWindowMenu::selectMode(QImage img, int trimSelect){
    if(formAndCrop!=nullptr){
        this->layout()->removeWidget(formAndCrop);
        formAndCrop->clearImage();
    }

    modState = trimSelect;
    formAndCrop = new FormsAndCrop(scrollAreaForImage->x(), scrollAreaForImage->y(),
                                         scrollAreaForImage->height()-scrollAreaForImage->horizontalScrollBar()->height(),
                                          scrollAreaForImage->width()-scrollAreaForImage->verticalScrollBar()->width(),trimSelect, scrollAreaForImage);
    mode = 3;
    this->layout()->addWidget(formAndCrop);
    actionRogner->setEnabled(true);


}

void mainWindowMenu::deleteSelec(QImage img,int trimSelect){


    if(trimSelect ==1){
        for(int i=formAndCrop->x; i<=formAndCrop->lastPoint.x();i++)
        {
            for(int j=formAndCrop->y;j<=formAndCrop->lastPoint.y();j++){
                img.setPixelColor(i, j, Qt::transparent);
            }
        }
    }
    else if(trimSelect == 2){
        QPainterPath path;
        path.moveTo(formAndCrop->x, formAndCrop->y);
        path.addEllipse(formAndCrop->x,formAndCrop->y,formAndCrop->lastP,formAndCrop->firstP);

        for(int i=formAndCrop->x; i<=formAndCrop->lastPoint.x();i++){
            for(int j=formAndCrop->y; j<=formAndCrop->lastPoint.y();j++){
                QPointF const *newPoint = new QPointF(i, j);
                if(path.contains(*newPoint))
                    img.setPixelColor(i, j, Qt::transparent);
            }
        }

    }
    theImg = img;
    formAndCrop->clearImage();
    refreshImage();
}


void mainWindowMenu::resizeEvent(QResizeEvent *event){
    scrollAreaForImage->setFixedHeight(this->height()-scrollAreaForImage->horizontalScrollBar()->height());
    scrollAreaForImage->setFixedWidth(this->width());
    if(formAndCrop!=nullptr){
        this->layout()->removeWidget(formAndCrop);
        formAndCrop->clearImage();
    }

    switch(mode){
        case 1:
            invertPixel();
            break;
        case 2:
            doResizing(theImg,0,0);
            break;
        case 3:
            selectMode(theImg,modState);
            break;

        default:
            mode=0;
    }

}

void mainWindowMenu::runAllEventFromTheMainWindow(){

    connect(actionQuit, &QAction::triggered, this, &mainWindowMenu::close);
    connect(actionOpenImage, &QAction::triggered, this, &mainWindowMenu::openNewFile);
    connect(actionCloseImage, &QAction::triggered, this, &mainWindowMenu::closeFile);
    connect(actionSave, &QAction::triggered, this, &mainWindowMenu::saveFile);
    connect(actionInverser_Pixels, &QAction::triggered, this, &mainWindowMenu::invertPixel);
    connect(actionHorizontal, &QAction::triggered, this, &mainWindowMenu::mirroiredH);
    connect(actionVertical, &QAction::triggered, this, &mainWindowMenu::mirroiredV);
    //connect(actionRedimensionnement, &QAction::triggered, this, [this]{doResizing(theImg);});
    connect(action1980_par_1024, &QAction::triggered, this, [this]{doResizing(theImg,1980,1024);});
    connect(action1600_par_900, &QAction::triggered, this, [this]{doResizing(theImg,1600,900);});
    connect(action1680_par_1050, &QAction::triggered, this, [this]{doResizing(theImg,1680,1050);});
    connect(action1024_par_768, &QAction::triggered, this, [this]{doResizing(theImg,1024,768);});
    connect(actionRectangle, &QAction::triggered, this, [this]{selectMode(theImg,1);});
    connect(actionCercle, &QAction::triggered, this, [this]{selectMode(theImg,2);});
    connect(actionRogner, &QAction::triggered, this, [this]{doTrim(theImg,modState);});
    connect(actionSupprimer, &QAction::triggered, this, [this]{deleteSelec(theImg,modState);});
    addShortCutToAction();


}

void mainWindowMenu::initSize(){
    scrollAreaForImage->setFixedHeight(this->height()-menubar->height());
    scrollAreaForImage->setFixedWidth(this->width());
}

void mainWindowMenu::setMenuEnabled(bool valueMenuEnabled){
    actionCloseImage->setEnabled(valueMenuEnabled);
    actionSave->setEnabled(valueMenuEnabled);
    menuRetouche->setEnabled(valueMenuEnabled);
    menuSelection->setEnabled(valueMenuEnabled);
}

void mainWindowMenu::addShortCutToAction(){
    actionOpenImage->setShortcut(QKeySequence(Qt::Key_O + Qt::CTRL));
    actionQuit->setShortcut(QKeySequence(Qt::Key_Q + Qt::CTRL));
    actionSave->setShortcut(QKeySequence(Qt::Key_S + Qt::CTRL));
    actionCloseImage->setShortcut(QKeySequence(Qt::Key_W + Qt::CTRL));
}

void mainWindowMenu::refreshImage(){
    labelForImage->setPixmap(QPixmap::fromImage(theImg));
    labelForImage->setVisible(true);
    scrollAreaForImage->setVisible(true);
    labelForImage->setFixedHeight(theImg.height());
    labelForImage->setFixedWidth(theImg.width());
}

mainWindowMenu::~mainWindowMenu()
{
}

