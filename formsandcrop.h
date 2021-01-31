#ifndef FORMSANDCROP_H
#define FORMSANDCROP_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QScrollArea>
#include <QLabel>
#include <iostream>
#include <QPainter>
#include <QMainWindow>
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPainterPath>
#include "displaycontains.h"
#include "imageforchange.h"


class FormsAndCrop : public QWidget
{

    Q_OBJECT
public:
    FormsAndCrop(int x, int y, int height, int width, int trimSelect, QScrollArea *scrollArea, DisplayContains* displayContains,
                 ImageForChange *imgForChange);
    int x = 0;
    int y = 0;


    static int xCrop;
    static int yCrop;
    int lastP =0;
    int firstP = 0;

    int xScroll;
    int yScroll;
    QPoint lastPoint;

    QImage image;


public slots:

    void clearImage();
    //void print();
    QImage doTrim(QImage img, int trimSelect, QLabel* labelForImage);
    void zoom(ImageForChange *image, DisplayContains * displCont);
    void dezoom(ImageForChange *image, DisplayContains *displCont);

    void drawLineTo(const QPoint &endPoint);
    void displayContainsCrop(int x,int y,int lastP, int firstP);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void pictureArea();

//    void resizeEvent(QResizeEvent *event) override;


private:
    void drawFormTo(const QPoint &endPoint);

//    void resizeImage(QImage *image, const QSize &newSize);

    bool modified = false;
    bool scribbling = false;
    int myPenWidth = 1;
    QColor myPenColor = Qt::black;
    int trimSelect;
    QScrollArea *scroll;
    QLabel* labelForImage;
    ImageForChange *imgForChange;
    DisplayContains* displayContains = nullptr;
    QImage newImage;
    QPainter painter;


};




#endif // FORMSANDCROP_H
