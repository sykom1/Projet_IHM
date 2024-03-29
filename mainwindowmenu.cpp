#include "mainwindowmenu.h"
#include "filters.h"
#include <QTranslator>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>
#include <string>


mainWindowMenu::mainWindowMenu(QTranslator *t, QStringList langues, QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    translator = t;
    this->langues = langues;
    setWindowTitle(tr("Retouche d'Image"));

    displayContains = new DisplayContains(this, menubar->height(), this->width(), this->height()-menubar->height());
    displayContains->setFixedHeight(this->height());
    displayContains->setFixedWidth(this->width());
    displayContains->move(0, menubar->height());
    imageForChange = new ImageForChange(action_Revenir, actionRevenir_en_avant,displayContains);
    runAllEventFromTheMainWindow();
    menuFiltre->setEnabled(true);
    menuActions->setEnabled(false);
    initLogo();
    loadSettings = new LoadSettings(this, translator);
    loadSettings->loadAllConfig();
    pathForFileImg = loadSettings->getPathFileForImg();
    fillListQAction();
}

void mainWindowMenu::initLogo(){
    actionRectangle->setIcon(QIcon(":/Resources/square.png"));
    actionCercle->setIcon(QIcon(":/Resources/rond.png"));
    actionDessiner->setIcon(QIcon(":/Resources/crayon.png"));
    actionRogner->setIcon(QIcon(":/Resources/rognage.png"));
    actionSupprimer->setIcon(QIcon(":/Resources/del.png"));
    actionReturnInitImg->setIcon(QIcon(":/Resources/ImageInitiale.png"));
    action_Revenir->setIcon(QIcon(":/Resources/RetourArriere.png"));
    actionRevenir_en_avant->setIcon(QIcon(":/Resources/RetourAvant.png"));

    actionSaveOn->setIcon(QIcon(":/Resources/EnregistrerSous.png"));
    actionSave->setIcon(QIcon(":/Resources/Enregistrer.png"));
    actionZoom->setIcon(QIcon(":/Resources/zoom.png"));
    actionDeZoom->setIcon(QIcon(":/Resources/dezoom.png"));

    actionOpenImage->setIcon(QIcon(":/Resources/OuvrirDoc.png"));
    menuRedimensionnement->setIcon(QIcon(":/Resources/redimentionner.png"));

    actionHorizontal->setIcon(QIcon(":/Resources/Horizontal.png"));
    actionVertical->setIcon(QIcon(":/Resources/Vertical.png"));

    actionConfig->setIcon(QIcon(":/Resources/param.png"));
    actionCloseImage->setIcon(QIcon(":/Resources/FermerDoc.png"));
}

DisplayContains* mainWindowMenu::getDisplayContains(){
    return this->displayContains;
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
            displayContains->refreshImage(imageForChange->getActualImg(), 0, 0);
            imageForChange->changeSizeReduceImg();
            displayContains->createNewReducedLabel(imageForChange->getReduceImg());
            displayContains->refreshReducedImage(imageForChange->getReduceImg());
            displayContains->moveReducedLabel(620, 30);
            displayContains->changeSizeOfScrollBar(this->width(), this->height());
            setMenuEnabled(true);
            if(barButtonRetouch!=nullptr){
                barButtonRetouch->recreateFormsAndCrop();
            }else{
                barButtonRetouch = new BarButtonRetouch(imageForChange, displayContains,actionRogner,actionSupprimer, this);
                barButtonRetouch->show();
            }
        }
    }



}

void mainWindowMenu::wheelEvent(QWheelEvent *wheelEvent)
{

    if(barButtonRetouch!=nullptr){
        QImage img = imageForChange->getActualImg();
        int width = imageForChange->getActualImg().width();
        int height = imageForChange->getActualImg().height();
        if(QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier)){
            if(wheelEvent->delta()>0){
                img = img.scaled(width*1.15,height*1.15,Qt::IgnoreAspectRatio,Qt::FastTransformation);
                imageForChange->changeActualImg(img);
                displayContains->refreshImage(imageForChange->getActualImg(), displayContains->getScrollArea()->x(), displayContains->getScrollArea()->y());
            }
            else{
                img = img.scaled(width*0.85,height*0.85,Qt::IgnoreAspectRatio,Qt::FastTransformation);
                imageForChange->changeActualImg(img);
                displayContains->refreshImage(imageForChange->getActualImg(), displayContains->getScrollArea()->x(), displayContains->getScrollArea()->y());
            }
        }
    }
}



void mainWindowMenu::closeEvent(QCloseEvent *event){
    int rep = QMessageBox::question(this,tr("Fermer le programme"),tr("Voulez vous vraiment fermer le programme?"),QMessageBox::Yes,QMessageBox::No);


    switch(rep){

    case QMessageBox::Yes:
        barButtonRetouch->close();
        event->accept();
        break;

    case QMessageBox::No:
        event->ignore();
        break;

    }
}

void mainWindowMenu::closeFile(){
    displayContains->clearDisplay();
    barButtonRetouch->closeFormsAndCrop();
    pathImg = nullptr;
    setMenuEnabled(false);
    if(barButtonRetouch!=nullptr)
    {
        barButtonRetouch->recreateFormsAndCrop();
        barButtonRetouch->close();
        barButtonRetouch = nullptr;
    }
}



void mainWindowMenu::saveFileOn(){
    QString pathImg = "";
    if(pathForFileImg!=nullptr)
        pathImg +=(pathForFileImg + "/");
    pathImg+=QString::fromStdString(nameImage);
    QString fileNameSave = QFileDialog::getSaveFileName(this,
                                                        tr("Sauvegarder l'image"), pathImg,
                                                        tr("Fichier Image") +"(*.png *.jpg *.bmp)");
    imageForChange->saveImg(fileNameSave);
    pathImg = fileNameSave;
    imageForChange->changeActualReduceImage();
    imageForChange->changeSizeReduceImg();
    displayContains->refreshReducedImage(imageForChange->getReduceImg());
}

void mainWindowMenu::saveFile(){
    if(pathImg!=nullptr){
        imageForChange->saveImg(pathImg);
        imageForChange->changeActualReduceImage();
        imageForChange->changeSizeReduceImg();
        displayContains->refreshReducedImage(imageForChange->getReduceImg());
    }else{
        saveFileOn();
    }
}

void mainWindowMenu::zoom(){
    barButtonRetouch->getFormsAndCrop()->zoom(imageForChange,displayContains);
}

void mainWindowMenu::dezoom(){
    barButtonRetouch->getFormsAndCrop()->dezoom(imageForChange,displayContains);
}

void mainWindowMenu::openColorParameter(){
    QImage imgAnnul = this->imageForChange->getActualImg();
    this->imageForChange->setFilterImg(this->imageForChange->getActualImg());
    colorParameter *colorParam = new colorParameter(this->imageForChange,this->displayContains,imgAnnul);
    colorParam->show();
}

void mainWindowMenu::doResizing(QImage img, int x,int y){
    resizePicture *picture = new resizePicture();
    displayContains->refreshImage(picture->resize(imageForChange->getActualImg(), x, y), 0, 0);
    imageForChange->changeActualImg(picture->resize(imageForChange->getActualImg(), x, y));
}


void mainWindowMenu::doResizing(QImage img){

    dialog.setWindowTitle(tr("Redimensionnement"));

    QFormLayout form(&dialog);

    name->setText(tr("Veuillez choisir le format de l'image :"));
    form.addRow(name);


    QList<QLineEdit *> fields;

    labelHauteur->setText(tr("Hauteur"));
    form.addRow(labelHauteur,lineEdit);
    fields << lineEdit;
    labelLargeur->setText(tr("Largeur"));
    form.addRow(labelLargeur,lineEdit2);
    fields << lineEdit2;


    QPushButton *button = new QPushButton;
    button->setText(tr("Valider"));
    form.addRow(button);

    connect(button,&QPushButton::clicked,&dialog,[this]{resizeClicked(lineEdit,lineEdit2,&dialog,imageForChange->getActualImg());});


    dialog.exec();

}


void mainWindowMenu::resizeClicked(QLineEdit *lineEdit, QLineEdit *lineEdit2,QDialog *qdialog,QImage img){
    bool lineEditBoolean1 = true;
    bool lineEditBoolean2 = true;

    if((lineEdit->text().toInt() >= 0 && lineEdit->text().toInt() <= 1980) && (lineEdit2->text().toInt() >=0 && lineEdit2->text().toInt() <= 1024)){
        doResizing(img,lineEdit->text().toInt(),lineEdit2->text().toInt());
        dialog.close();
    } else
    {
        QMessageBox msgBox;
        msgBox.setText("Une erreur est survenue.");
        if(lineEdit->text().toInt() < 0  || lineEdit->text().toInt() > 1980){
            lineEditBoolean1 = false;
        }
        if(lineEdit2->text().toInt() < 0 || lineEdit2->text().toInt() > 1024)
        {
            lineEditBoolean2 = false;
        }

        if(lineEditBoolean1==false && lineEditBoolean2==false){
            msgBox.setText("Veuillez saisir une largeur ET une hauteur valide !");
        }
        if(lineEditBoolean1==true && lineEditBoolean2 == false){
            msgBox.setText("Veuillez saisisr une largeur valide");
        }
        if(lineEditBoolean1==false && lineEditBoolean2==true){
            msgBox.setText("Veuillez saisir une hauteur valide");
        }
        msgBox.exec();
    }
}


void mainWindowMenu::doTrim(QImage img, int trimSelect){
       barButtonRetouch->doTrim();
}

void mainWindowMenu::selectMode(QImage img, int trimSelect){
    barButtonRetouch->closeFormsAndCrop();

    switch(trimSelect){
        case BarButtonRetouch::Square:
            barButtonRetouch->squareSelectButton();
            break;
        case BarButtonRetouch::Circle:
            barButtonRetouch->circleSelectButton();
            break;
    }

    //barButtonRetouch->selectMode((BarButtonRetouch::Selection)trimSelect);
    actionRogner->setEnabled(true);


}

void mainWindowMenu::deleteSelec(QImage img,int trimSelect){

    barButtonRetouch->deleteSelec();
}


void mainWindowMenu::moveEvent(QMoveEvent *event)
{
     if(barButtonRetouch!=nullptr)
        barButtonRetouch->moveColorWindow();

    QMainWindow::moveEvent(event);
}

QTranslator* mainWindowMenu::getTranslation(){
    return this->translator;
}

void mainWindowMenu::resizeEvent(QResizeEvent *event){
    displayContains->changeSizeOfScrollBar(this->width(), this->height());

    if(barButtonRetouch != nullptr){
        barButtonRetouch->recreateFormsAndCrop();
        barButtonRetouch->moveColorWindow();
        barButtonRetouch->moveMenu();
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

void mainWindowMenu::fillListQAction(){
    listQActionFile->append(actionOpenImage);
    listQActionFile->append(actionSaveOn);
    listQActionFile->append(actionSave);
    listQActionFile->append(actionQuit);
    listQActionFile->append(actionCloseImage);

    listQActionRetouch->append(actionHorizontal);
    listQActionRetouch->append(actionVertical);
    listQActionRetouch->append(actionInverser_Pixels);
    listQActionRetouch->append(actionSupprimer);
    listQActionRetouch->append(actionRogner);
    listQActionRetouch->append(actionReturnInitImg);
    listQActionRetouch->append(actionGreen_Filter);
    listQActionRetouch->append(actionRed_Filter);
    listQActionRetouch->append(actionBlue_Filter);

    listQActionSelection->append(actionRectangle);
    listQActionSelection->append(actionCercle);

    listQActionEdition->append(action_Revenir);
    listQActionEdition->append(actionRevenir_en_avant);

    listofListQAction->append(listQActionFile);
    listofListQAction->append(listQActionRetouch);
    listofListQAction->append(listQActionSelection);
    listofListQAction->append(listQActionEdition);
}

void mainWindowMenu::updateLanguage(const QString language) {
    QString pathFile = QApplication::applicationDirPath().left(1)+":/options.ini";
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, pathFile);
    QString translations = QString(":/"+language.toLower()+".qm");
    settings.setValue("langue", language);
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
    connect(actionDeZoom, &QAction::triggered,this,&mainWindowMenu::dezoom);
    connect(actionRed_Filter, &QAction::triggered, this, [this]{filters::redFilter(imageForChange,displayContains);});
    connect(actionGreen_Filter, &QAction::triggered, this, [this]{filters::greenFilter(imageForChange,displayContains);});
    connect(actionBlue_Filter, &QAction::triggered, this, [this]{filters::blueFilter(imageForChange,displayContains);});
    connect(actionPersonnalised, &QAction::triggered, this, &mainWindowMenu::openColorParameter);
    connect(action1980_par_1024, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1980,1024);});
    connect(action1600_par_900, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1600,900);});
    connect(action1680_par_1050, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1680,1050);});
    connect(action1024_par_768, &QAction::triggered, this, [this]{doResizing(imageForChange->getActualImg(),1024,768);});
    connect(actionPersonnalis_e,&QAction::triggered,this,[this]{doResizing(imageForChange->getActualImg());});
    connect(actionRectangle, &QAction::triggered, this, [this]{barButtonRetouch->squareSelectButton();});
    connect(actionCercle, &QAction::triggered, this, [this]{barButtonRetouch->circleSelectButton();});
    connect(actionRogner, &QAction::triggered, this, [this]{doTrim(imageForChange->getActualImg(),barButtonRetouch->getModState());});
    connect(actionSupprimer, &QAction::triggered, this, [this]{deleteSelec(imageForChange->getActualImg(),barButtonRetouch->getModState());});
    connect(actionReturnInitImg, &QAction::triggered, this, [this]{barButtonRetouch->initImgFct();});
    connect(actionDessiner, &QAction::triggered, this, [this]{barButtonRetouch->drawSelectButton();});
    connect(action_Revenir, &QAction::triggered, this, [this]{
        if(imageForChange->isPrevious()){
            imageForChange->retourArriere();
            displayContains->changeSizeOfScrollBar(this->width(), this->height());
            if(barButtonRetouch!=nullptr){
                barButtonRetouch->recreateFormsAndCrop();
            }
        }});
    connect(actionRevenir_en_avant, &QAction::triggered, this, [this]{
        if(imageForChange->isNext()){
            imageForChange->retourAvant();
            displayContains->changeSizeOfScrollBar(this->width(), this->height());
            if(barButtonRetouch!=nullptr){
                barButtonRetouch->recreateFormsAndCrop();
            }
        }});

    connect(actionConfig, &QAction::triggered, this, &mainWindowMenu::openSettings);

    addShortCutToAction();


}

void mainWindowMenu::openSettings(){
    if(menuSettings!=nullptr){
        menuSettings->close();
        menuSettings = nullptr;
    }
    menuSettings = new MenuSettings(langues, translator, loadSettings, listofListQAction);
    menuSettings->show();
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

