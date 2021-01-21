#include "mainwindowmenu.h"
#include <QTranslator>




mainWindowMenu::mainWindowMenu(QTranslator *t, QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    translator = t;
    setWindowTitle(tr("Retouche d'Image"));
    imageForChange = new ImageForChange();
    displayContains = new DisplayContains(this, menubar->height(), this->width(), this->height()-menubar->height());
    displayContains->setFixedHeight(this->height());
    displayContains->setFixedWidth(this->width());
    displayContains->move(0, menubar->height());
    runAllEventFromTheMainWindow();
    actionRogner->setEnabled(false);
    menuFiltre->setEnabled(true);
    /*Ui::mainWindowMenu ui;
    QActionGroup* langGroup = new QActionGroup(ui.menuLangues);
    langGroup->setExclusive(true);  */


}

void mainWindowMenu::openNewFile(){
    QString pathImage = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Sélectionnez l'image"),
                                                                              QDir::currentPath(), tr("Fichier Image") +"(*.png *.jpg *.bmp)"));
    QImageReader readerImage(pathImage);
    QImageReader readerImageInit(pathImage);
    QImageReader readerReduceImage(pathImage);
    readerImage.setAutoTransform(true);

    imageForChange->initImgWithPath(pathImage);
    if(!displayContains->reducedLabelIsNull()){
        displayContains->removeParentForReducedLabel();
    }
    if(!imageForChange->isNull()){
        displayContains->refreshImage(imageForChange->getActualImg());
        imageForChange->changeSizeReduceImg();
        //refreshReduceImage();
        displayContains->createNewReducedLabel(imageForChange->getReduceImg());
        displayContains->refreshReducedImage(imageForChange->getReduceImg());
        displayContains->moveReducedLabel(620, 30);
        setMenuEnabled(true);
    }
}

void mainWindowMenu::closeFile(){
    displayContains->clearDisplay();
    pathImg = nullptr;
    setMenuEnabled(false);

}

void mainWindowMenu::saveFileOn(){
    QString fileNameSave = QFileDialog::getSaveFileName(this,
                                                        tr("Sauvegarder l'image"), "",
                                                        tr("Fichier Image") +"(*.png *.jpg *.bmp)");
    imageForChange->saveImg(fileNameSave);
    pathImg = fileNameSave;
}

void mainWindowMenu::saveFile(){
    if(pathImg!=nullptr){
        imageForChange->saveImg(pathImg);
    }else
        saveFileOn();
}

void mainWindowMenu::invertPixel(){
    QImage img = imageForChange->getActualImg();
    img.invertPixels();
    imageForChange->changeActualImg(img);
    //imageForChange->getActualImg().invertPixels();
    displayContains->refreshImage(imageForChange->getActualImg());
    std::cout << "rentrer dans la fonction filtre" << std::endl;
}

void mainWindowMenu::mirroiredH(){
    imageForChange->changeActualImg(imageForChange->getActualImg().mirrored(true, false));
    displayContains->refreshImage(imageForChange->getActualImg());
}

void mainWindowMenu::mirroiredV(){
    imageForChange->changeActualImg(imageForChange->getActualImg().mirrored(false, true));
    displayContains->refreshImage(imageForChange->getActualImg());
}

void mainWindowMenu::doResizing(QImage img, int x,int y){
    resizePicture *picture = new resizePicture();
    imageForChange->changeActualImg(picture->resize(imageForChange->getActualImg(), x, y));
    displayContains->refreshImage(imageForChange->getActualImg());
}

void mainWindowMenu::doTrim(QImage img, int trimSelect){

       imageForChange->changeActualImg(formAndCrop->doTrim(img,trimSelect,displayContains->getLabelForImage()));
            if(trimSelect== 1){
                displayContains->refreshImage(imageForChange->getActualImg());
                displayContains->moveScrollArea(formAndCrop->x, formAndCrop->y);
            }


    //            theImg = img.copy(formAndCrop->x,formAndCrop->y,formAndCrop->lastP,formAndCrop->firstP );
    //            refreshImage();
    //            scrollAreaForImage->move(formAndCrop->x, formAndCrop->y);
    //        }
    //        else if(trimSelect == 2){

    //            QPixmap target = QPixmap(size());
    //            target.fill(Qt::transparent);

    //            QPixmap p = QPixmap::fromImage(img);
    //            //p.scaled(200, 200, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);


    //            QPainter painter (&target);

    //            painter.setRenderHint(QPainter::Antialiasing, true);
    //            painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    //            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    //            QPainterPath path = QPainterPath();
    //           // path.addRoundedRect(formAndCrop->x,formAndCrop->y, formAndCrop->lastP,formAndCrop->firstP, 50, 50);
    //            path.addEllipse(formAndCrop->x,formAndCrop->y, formAndCrop->lastP,formAndCrop->firstP);

    //            painter.setClipPath(path);
    //            painter.drawPixmap(0, 0, p);
    //            labelForImage->setPixmap(target);
    //            theImg = target.toImage();

    //        }

    //        formAndCrop->clearImage();
    //       // scrollAreaForImage->move(formAndCrop->x, formAndCrop->y);
    //    }




}

void mainWindowMenu::selectMode(QImage img, int trimSelect){
    if(formAndCrop!=nullptr){
        this->layout()->removeWidget(formAndCrop);
        formAndCrop->clearImage();
    }

    modState = trimSelect;
    formAndCrop = new FormsAndCrop(displayContains->getScrollArea()->x(),
                                   displayContains->getScrollArea()->y(),
                                   displayContains->getScrollArea()->height()-displayContains->getScrollArea()->horizontalScrollBar()->height(),
                                   displayContains->getScrollArea()->width()-displayContains->getScrollArea()->verticalScrollBar()->width(),trimSelect,
                                   displayContains->getScrollArea(),img, displayContains, imageForChange);
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
    imageForChange->changeActualImg(img);
    formAndCrop->clearImage();
    displayContains->refreshImage(imageForChange->getActualImg());
}


void mainWindowMenu::resizeEvent(QResizeEvent *event){
    displayContains->changeSizeOfScrollBar(this->width(), this->height());
    if(formAndCrop!=nullptr){
        this->layout()->removeWidget(formAndCrop);
        formAndCrop->clearImage();
    }

    switch(mode){
        case 1:
            invertPixel();
            break;
        case 2:
            doResizing(imageForChange->getActualImg(),0,0);
            break;
        case 3:
            selectMode(imageForChange->getActualImg(),modState);
            break;

        default:
            mode=0;
    }

}

void mainWindowMenu::changeEvent(QEvent *event){
    if(event->type() == QEvent::LanguageChange){
        setWindowTitle(tr("Retouche d'Image"));
        // File menu
        menuFile->setTitle(tr("Fichier"));
        actionOpenImage->setText("&"+tr("Ouvrir une image"));
        actionSaveOn->setText("&" + tr("Sauvegarder sous"));
        actionQuit->setText("&" + tr("Quitter"));
        actionCloseImage->setText("&" + tr("Fermer l'image"));
        actionSave->setText("&" + tr("Sauvegarder"));

        // Retouch menu
        menuRetouche->setTitle("&" + tr("Retouche"));
        menuRedimensionnement->setTitle("&" + tr("Redimensionnement"));
        menuFiltre->setTitle("&" + tr("Filtre"));
        menuMiroir->setTitle("&" + tr("Miroir"));
        actionHorizontal->setText("&" + tr("Horizontal"));
        actionHorizontal->setText("&" + tr("Vertical"));
        actionInverser_Pixels->setText("&" + tr("Inverser Pixels"));
        actionSupprimer->setText("&" + tr("Supprimer"));
        actionRogner->setText("&" + tr("Rogner"));
        actionReturnInitImg->setText("&" + tr("Retour à l'image initiale"));

        // Selection Menu
        menuSelection->setTitle("&" + tr("Selection"));
        actionRectangle->setText("&" + tr("Rectangle"));
        actionCercle->setText("&" + tr("Cercle"));





    }
}

void mainWindowMenu::updateLanguage(const QString language) {
    QString translations = QString(":/"+language.toLower()+".qm");
    translator->load(translations);
}

void mainWindowMenu::runAllEventFromTheMainWindow(){

    connect(actionQuit, &QAction::triggered, this, &mainWindowMenu::close);
    connect(actionOpenImage, &QAction::triggered, this, &mainWindowMenu::openNewFile);
    connect(actionCloseImage, &QAction::triggered, this, &mainWindowMenu::closeFile);
    connect(actionSaveOn, &QAction::triggered, this, &mainWindowMenu::saveFileOn);
    connect(actionSave, &QAction::triggered, this, &mainWindowMenu::saveFile);
    connect(actionInverser_Pixels, &QAction::triggered, this, &mainWindowMenu::invertPixel);
    connect(actionHorizontal, &QAction::triggered, this, &mainWindowMenu::mirroiredH);
    connect(actionVertical, &QAction::triggered, this, &mainWindowMenu::mirroiredV);
    connect(action1980_par_1024, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1980,1024);});
    connect(action1600_par_900, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1600,900);});
    connect(action1680_par_1050, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1680,1050);});
    connect(action1024_par_768, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1024,768);});
    connect(actionRectangle, &QAction::triggered, this, [this]{selectMode(imageForChange->getActualImg(),1);});
    connect(actionCercle, &QAction::triggered, this, [this]{selectMode(imageForChange->getActualImg(),2);});
    connect(actionRogner, &QAction::triggered, this, [this]{doTrim(imageForChange->getActualImg(),modState);});
    connect(actionSupprimer, &QAction::triggered, this, [this]{deleteSelec(imageForChange->getActualImg(),modState);});
    connect(actionFrancais, &QAction::triggered, this, [this]{updateLanguage("Francais");});
    connect(actionAnglais, &QAction::triggered, this, [this]{updateLanguage("English");});
    connect(actionReturnInitImg, &QAction::triggered, this, &mainWindowMenu::initImgDisplay);
    connect(actionDessiner, &QAction::triggered, this, [this]{selectMode(imageForChange->getActualImg(),3);});
    addShortCutToAction();


}

void mainWindowMenu::initImgDisplay(){
    imageForChange->initActualImg();
    displayContains->refreshImage(imageForChange->getActualImg());
}

void mainWindowMenu::setMenuEnabled(bool valueMenuEnabled){
    actionCloseImage->setEnabled(valueMenuEnabled);
    actionSaveOn->setEnabled(valueMenuEnabled);
    actionSave->setEnabled(valueMenuEnabled);
    menuRetouche->setEnabled(valueMenuEnabled);
    menuSelection->setEnabled(valueMenuEnabled);
}

void mainWindowMenu::addShortCutToAction(){
    actionOpenImage->setShortcut(QKeySequence(Qt::Key_O + Qt::CTRL));
    actionQuit->setShortcut(QKeySequence(Qt::Key_Q + Qt::CTRL));
    actionSaveOn->setShortcut(QKeySequence(Qt::Key_S + Qt::CTRL + Qt::ALT));
    actionSave->setShortcut(QKeySequence(Qt::Key_S + Qt::CTRL));
    actionCloseImage->setShortcut(QKeySequence(Qt::Key_W + Qt::CTRL));
}

mainWindowMenu::~mainWindowMenu()
{
}

