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
    initSize();
    labelForImage = new QLabel();
    scrollAreaForImage->setWidget(labelForImage);
    labelForImage->setVisible(false);
    scrollAreaForImage->setVisible(false);
    runAllEventFromTheMainWindow();
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
    // TODO
    std::cout << "saveFile function on" << std::endl;
}

void mainWindowMenu::doFilter(QImage img){
    //TODO
    std::cout << "rentrer dans la fonction filtre" << std::endl;
}

void mainWindowMenu::doResizing(QImage img){
    //TODO
}

void mainWindowMenu::doTrim(QImage img, int trimSelect){
//    formAndCrop = new FormsAndCrop(scrollAreaForImage->x(), scrollAreaForImage->y(),
//                                         scrollAreaForImage->height()-scrollAreaForImage->horizontalScrollBar()->height(),
//                                          scrollAreaForImage->width()-scrollAreaForImage->verticalScrollBar()->width());
//    mode = 3;
//    this->layout()->addWidget(formAndCrop);

    theImg = img.copy(formAndCrop->x,formAndCrop->y,formAndCrop->lastP,formAndCrop->firstP );
    formAndCrop->clearImage();
    refreshImage();
    scrollAreaForImage->move(formAndCrop->x, formAndCrop->y);
}

void mainWindowMenu::selectMode(QImage img, int trimSelect){
    if(formAndCrop!=nullptr){
        this->layout()->removeWidget(formAndCrop);
        formAndCrop->clearImage();
    }
    modState = trimSelect;
    formAndCrop = new FormsAndCrop(scrollAreaForImage->x(), scrollAreaForImage->y(),
                                         scrollAreaForImage->height()-scrollAreaForImage->horizontalScrollBar()->height(),
                                          scrollAreaForImage->width()-scrollAreaForImage->verticalScrollBar()->width(),trimSelect);
    mode = 3;
    this->layout()->addWidget(formAndCrop);


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
            doFilter(theImg);
            break;
        case 2:
            doResizing(theImg);
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
    connect(actionFiltre, &QAction::triggered, this, [this]{doFilter(theImg);});
    connect(actionRedimensionnement, &QAction::triggered, this, [this]{doResizing(theImg);});
    connect(actionRectangle, &QAction::triggered, this, [this]{selectMode(theImg,1);});
    connect(actionCercle, &QAction::triggered, this, [this]{selectMode(theImg,2);});
    connect(actionRogner, &QAction::triggered, this, [this]{doTrim(theImg,modState);});
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
    actionOpenImage->setShortcut(QKeySequence(Qt::Key_N + Qt::CTRL));
    actionQuit->setShortcut(QKeySequence(Qt::Key_X + Qt::CTRL));
    actionSave->setShortcut(QKeySequence(Qt::Key_S + Qt::CTRL));
    actionCloseImage->setShortcut(QKeySequence(Qt::Key_A + Qt::CTRL));
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

