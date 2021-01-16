#include "mainwindowmenu.h"

mainWindowMenu::mainWindowMenu(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    setWindowTitle(tr("Retouche d'Image"));
    scrollAreaForImage = new QScrollArea(this);
    scrollAreaForImage->move(0,menubar->height());
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
        labelForImage->setPixmap(QPixmap::fromImage(theImg));
        labelForImage->setVisible(true);
        scrollAreaForImage->setVisible(true);
        labelForImage->setFixedHeight(theImg.height());
        labelForImage->setFixedWidth(theImg.width());
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

void mainWindowMenu::doTrim(QImage img){
    //TODO
}

void mainWindowMenu::runAllEventFromTheMainWindow(){
    connect(actionQuit, &QAction::triggered, this, &mainWindowMenu::close);
    connect(actionOpenImage, &QAction::triggered, this, &mainWindowMenu::openNewFile);
    connect(actionCloseImage, &QAction::triggered, this, &mainWindowMenu::closeFile);
    connect(actionSave, &QAction::triggered, this, &mainWindowMenu::saveFile);
    connect(actionFiltre, &QAction::triggered, this, [this]{doFilter(theImg);});
    connect(actionRedimensionnement, &QAction::triggered, this, [this]{doResizing(theImg);});
    connect(actionRogner, &QAction::triggered, this, [this]{doTrim(theImg);});
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
}

void mainWindowMenu::addShortCutToAction(){
    actionOpenImage->setShortcut(QKeySequence(Qt::Key_N + Qt::CTRL));
    actionQuit->setShortcut(QKeySequence(Qt::Key_X + Qt::CTRL));
    actionSave->setShortcut(QKeySequence(Qt::Key_S + Qt::CTRL));
    actionCloseImage->setShortcut(QKeySequence(Qt::Key_A + Qt::CTRL));
}

mainWindowMenu::~mainWindowMenu()
{
}

