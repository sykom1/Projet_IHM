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


class FormsAndCrop : public QWidget
{
public:
    FormsAndCrop(int x, int y, int height, int width, int trimSelect, QScrollArea *scrollArea);
    int x = 0;
    int y = 0;

    int lastP;
    int firstP;
    QPoint lastPoint;



public slots:
    void clearImage();
    void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
//    void resizeEvent(QResizeEvent *event) override;


private:
    void drawLineTo(const QPoint &endPoint);
//    void resizeImage(QImage *image, const QSize &newSize);

    bool modified = false;
    bool scribbling = false;
    int myPenWidth = 1;
    QColor myPenColor = Qt::black;
    QImage image;
    int trimSelect;
    QScrollArea *scroll;



};




#endif // FORMSANDCROP_H
