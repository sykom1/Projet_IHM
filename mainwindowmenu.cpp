#include "mainwindowmenu.h"

mainWindowMenu::mainWindowMenu(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    labelForImage->setVisible(false);
    connect(actionQuit, &QAction::triggered, this, &mainWindowMenu::close);
    connect(actionOpenImage, &QAction::triggered, this, &mainWindowMenu::openNewFile);
}

void mainWindowMenu::openNewFile(){
    QString pathImage = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Sélectionnez l'image"),
                                                                              QDir::currentPath(), tr("Fichier Image (*.png *.jpg *.bmp)")));
    QImageReader readerImage(pathImage);
    readerImage.setAutoTransform(true);
    const QImage theImg = readerImage.read();
    if(!theImg.isNull()){
        labelForImage->setPixmap(QPixmap::fromImage(theImg));
        labelForImage->setVisible(true);
    }
}

mainWindowMenu::~mainWindowMenu()
{
}

