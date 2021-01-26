#include "mainwindowmenu.h"
#include "filters.h"
#include <QTranslator>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>


mainWindowMenu::mainWindowMenu(QTranslator *t, QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    translator = t;
    setWindowTitle(tr("Retouche d'Image"));
    imageForChange = new ImageForChange(action_Revenir, actionRevenir_en_avant);
    displayContains = new DisplayContains(this, menubar->height(), this->width(), this->height()-menubar->height());
    displayContains->setFixedHeight(this->height());
    displayContains->setFixedWidth(this->width());
    displayContains->move(0, menubar->height());
    runAllEventFromTheMainWindow();
    actionRogner->setEnabled(false);
    menuFiltre->setEnabled(true);
    menuActions->setEnabled(false);
}

void mainWindowMenu::openNewFile(){
    QString pathImage = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Sélectionnez l'image"),
                                                                              QDir::currentPath(), tr("Fichier Image") +"(*.png *.jpg *.bmp)"));
   /* QPushButton *boutonrevenir;
    QPushButton *boutonavancer; */
    if(!pathImage.isNull()){
        if(pathImage.contains("/"))
            nameImage = strrchr(pathImage.toStdString().c_str(), '/')+1;
        else
            nameImage = strrchr(pathImage.toStdString().c_str(), '\\') + 1;
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
            displayContains->changeSizeOfScrollBar(this->width(), this->height());
            setMenuEnabled(true);
        }

        //printPixels(imageForChange);
    }



}



void mainWindowMenu::closeEvent(QCloseEvent *event){
    int rep = QMessageBox::question(this,"Fermer le progarmme","Voulez vous vraiment fermer le programme?",QMessageBox::Yes,QMessageBox::No);


    switch(rep){

    case QMessageBox::Yes:
        event->accept();
        break;

    case QMessageBox::No:
        event->ignore();
        break;

    }
}

void mainWindowMenu::closeFile(){
    displayContains->clearDisplay();
    if(formAndCrop!=nullptr){
        formAndCrop->clearImage();
    }
    pathImg = nullptr;
    setMenuEnabled(false);

}



void mainWindowMenu::saveFileOn(){
    QString fileNameSave = QFileDialog::getSaveFileName(this,
                                                        tr("Sauvegarder l'image"), QString::fromStdString(nameImage),
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

void mainWindowMenu::zoom(){
    formAndCrop->zoom(imageForChange,displayContains);
}

void mainWindowMenu::doResizing(QImage img, int x,int y){
    resizePicture *picture = new resizePicture();
    imageForChange->changeActualImg(picture->resize(imageForChange->getActualImg(), x, y));
    displayContains->refreshImage(imageForChange->getActualImg());
}


void mainWindowMenu::doResizing(QImage img){

    dialog.setWindowTitle(tr("Redimensionnement"));

    QFormLayout form(&dialog);


    form.addRow(new QLabel(tr("Veuillez choisir le format de l'image :")));


    QList<QLineEdit *> fields;

    lineEdit = new QLineEdit(&dialog);
    QString label = QString(tr("Hauteur"));
    form.addRow(label,lineEdit);
    fields << lineEdit;

    lineEdit2 = new QLineEdit(&dialog);
    label = QString(tr("Largeur"));
    form.addRow(label,lineEdit2);
    fields << lineEdit2;


    QPushButton *button = new QPushButton;
    button->setText(tr("Confirmer"));
    form.addRow(button);

    connect(button,&QPushButton::clicked,&dialog,[this]{resizeClicked(lineEdit,lineEdit2,&dialog,imageForChange->getActualImg());});

//    connect(button,SIGNAL(clicked()),&dialog,SLOT(resizeClicked(QLineEdit,QLineEdit,QDialog,QImage)));

    dialog.exec();

}


void mainWindowMenu::resizeClicked(QLineEdit *lineEdit, QLineEdit *lineEdit2,QDialog *qdialog,QImage img){

    doResizing(img,lineEdit->text().toInt(),lineEdit2->text().toInt());
    dialog.close();
}


void mainWindowMenu::doTrim(QImage img, int trimSelect){

       imageForChange->changeActualImg(formAndCrop->doTrim(img,trimSelect,displayContains->getLabelForImage()));





}

void mainWindowMenu::selectMode(QImage img, int trimSelect){
    if(formAndCrop!=nullptr){
        this->layout()->removeWidget(formAndCrop);
        formAndCrop->clearImage();
    }


    modState = trimSelect;
    formAndCrop = new FormsAndCrop(displayContains->x(),
                                   displayContains->y(),
                                   displayContains->getScrollArea()->height()-displayContains->getScrollArea()->horizontalScrollBar()->height(),
                                   displayContains->getScrollArea()->width()-displayContains->getScrollArea()->verticalScrollBar()->width(),trimSelect,
                                   displayContains->getScrollArea(), displayContains, imageForChange);
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
                if(path.contains(*newPoint)){
                    if(i<imageForChange->getActualImg().width()&&j<imageForChange->getActualImg().height())
                        img.setPixelColor(i, j, Qt::transparent);
                }
            }
        }

    }
    imageForChange->changeActualImg(img);
    formAndCrop->clearImage();
    displayContains->refreshImage(imageForChange->getActualImg());
    displayContains->moveScrollArea(formAndCrop->xCrop, formAndCrop->yCrop);
}

void mainWindowMenu::colorMenu(){
    choseColor *test = new choseColor(this);

    test->show();
}

void mainWindowMenu::resizeEvent(QResizeEvent *event){
    displayContains->changeSizeOfScrollBar(this->width(), this->height());
    if(formAndCrop!=nullptr){
        formAndCrop->clearImage();
        formAndCrop->setFixedHeight(displayContains->getScrollArea()->height()-displayContains->getScrollArea()->horizontalScrollBar()->height());
        formAndCrop->setFixedWidth(displayContains->getScrollArea()->width()-displayContains->getScrollArea()->verticalScrollBar()->width());
        formAndCrop->move(0, menubar->height());
    }

//    switch(mode){
//        case 1:
//            invertPixel();
//            break;
//        case 2:
//            doResizing(imageForChange->getActualImg(),0,0);
//            break;
//        case 3:
//            selectMode(imageForChange->getActualImg(),modState);
//            break;

//        default:
//            mode=0;
//    }

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
        actionVertical->setText("&" + tr("Vertical"));
        actionInverser_Pixels->setText("&" + tr("Inverser Pixels"));
        actionSupprimer->setText("&" + tr("Supprimer"));
        actionRogner->setText("&" + tr("Rogner"));
        actionReturnInitImg->setText("&" + tr("Retour à l'image initiale"));
        actionGreen_Filter->setText("&" + tr("Green Color"));
        actionRed_Filter->setText("&" + tr("Red Color"));
        actionBlue_Filter->setText("&" + tr("Blue Color"));

        // Selection Menu
        menuSelection->setTitle("&" + tr("Selection"));
        actionRectangle->setText("&" + tr("Rectangle"));
        actionCercle->setText("&" + tr("Cercle"));

        // Langues Menu
        menuLangues->setTitle("&" + tr("Langues"));
        actionFrancais->setText("&" + tr("Français"));
        actionAnglais->setText("&" + tr("Anglais"));

        // Edition Menu
        menuEdition->setTitle("&" + tr("Edition"));
        action_Revenir->setText("&" + tr("Revenir en arrière"));
        actionRevenir_en_avant->setText("&" + tr("Revenir en avant"));

        //ResizeMenu
        menuRedimensionnement->setTitle("&" + tr("Redimensionnement"));
        action1024_par_768->setText("&" + tr("1024 par 768"));
        action1600_par_900->setText("&" + tr("1600 par 900"));
        action1680_par_1050->setText("&" + tr("1680 par 1050"));
        action1980_par_1024->setText("&" + tr("1980 par 1024"));
        actionPersonnalis_e->setText("&" + tr("Personnalisée"));



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
    connect(actionInverser_Pixels, &QAction::triggered, this, [this]{filters::invertPixel(imageForChange, displayContains);});
    connect(actionHorizontal, &QAction::triggered, this, [this]{filters::mirroredH(imageForChange,displayContains);});
    connect(actionVertical, &QAction::triggered, this, [this]{filters::mirroredV(imageForChange,displayContains);});
    connect(actionZoom, &QAction::triggered,this,&mainWindowMenu::zoom);
    connect(actionRed_Filter, &QAction::triggered, this, [this]{filters::redFilter(imageForChange,displayContains);});
    connect(actionGreen_Filter, &QAction::triggered, this, [this]{filters::greenFilter(imageForChange,displayContains);});
    connect(actionBlue_Filter, &QAction::triggered, this, [this]{filters::blueFilter(imageForChange,displayContains);});
    connect(action1980_par_1024, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1980,1024);});
    connect(action1600_par_900, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1600,900);});
    connect(action1680_par_1050, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1680,1050);});
    connect(action1024_par_768, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1024,768);});
    connect(actionPersonnalis_e,&QAction::triggered,this,[this]{doResizing(imageForChange->getActualImg());});
    connect(actionRectangle, &QAction::triggered, this, [this]{selectMode(imageForChange->getActualImg(),1);});
    connect(actionCercle, &QAction::triggered, this, [this]{selectMode(imageForChange->getActualImg(),2);});
    connect(actionRogner, &QAction::triggered, this, [this]{doTrim(imageForChange->getActualImg(),modState);});
    connect(actionSupprimer, &QAction::triggered, this, [this]{deleteSelec(imageForChange->getActualImg(),modState);});
    connect(actionFrancais, &QAction::triggered, this, [this]{updateLanguage("Francais");});
    connect(actionAnglais, &QAction::triggered, this, [this]{updateLanguage("English");});
    connect(actionReturnInitImg, &QAction::triggered, this, &mainWindowMenu::initImgDisplay);
    connect(actionDessiner, &QAction::triggered, this, [this]{selectMode(imageForChange->getActualImg(),3); colorMenu();});
    connect(action_Revenir, &QAction::triggered, this, [this]{imageForChange->retourArriere();displayContains->refreshImage(imageForChange->getActualImg());});
    connect(actionRevenir_en_avant, &QAction::triggered, this, [this]{imageForChange->retourAvant();displayContains->refreshImage(imageForChange->getActualImg());});

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
    menuActions->setEnabled(valueMenuEnabled);
}

void mainWindowMenu::addShortCutToAction(){
    actionOpenImage->setShortcut(QKeySequence(Qt::Key_O + Qt::CTRL));
    actionQuit->setShortcut(QKeySequence(Qt::Key_Q + Qt::CTRL));
    actionSaveOn->setShortcut(QKeySequence(Qt::Key_S + Qt::CTRL + Qt::ALT));
    actionSave->setShortcut(QKeySequence(Qt::Key_S + Qt::CTRL));
    actionCloseImage->setShortcut(QKeySequence(Qt::Key_W + Qt::CTRL));
    actionRevenir_en_avant->setShortcut(QKeySequence(Qt::Key_Z + Qt::CTRL + Qt::SHIFT));
    action_Revenir->setShortcut(QKeySequence(Qt::Key_Z + Qt::CTRL));
}

void mainWindowMenu::printPixels(ImageForChange *image){
    for(int i = 0; i < image->getActualImg().width();i++){
        for(int j = 0; j < image->getActualImg().height();j++){
            std::cout << "Couleur du pixel (" << i << "," <<  j << ") : " <<  image->getActualImg().pixelColor(i,j).blue() << std::endl;
        }
    }
}


ImageForChange* mainWindowMenu::getImageForChange(){
    return imageForChange;
}

mainWindowMenu::~mainWindowMenu()
{
}

