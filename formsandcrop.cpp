#include "formsandcrop.h"
#include <QMouseEvent>
#include <QPainter>

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
FormsAndCrop::FormsAndCrop(int x, int y, int height, int width,int trimSelect): QWidget()
{
    QImage newImage(QSize(width, height), QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0, 0, 0));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), image);
    image = newImage;
    this->move(x, y);
    this->setFixedWidth(width);
    this->setFixedHeight(height);
    this->trimSelect = trimSelect;

}


void FormsAndCrop::clearImage()

{
    image.convertToFormat(QImage::Format_ARGB32);
   // QImage image(image.size(), QImage::Format_ARGB32);
    image.fill(qRgba(255,255,255,0));

    modified = true;
    update();
}

void FormsAndCrop::mousePressEvent(QMouseEvent *event)

{

    if (event->button() == Qt::LeftButton) {

        lastPoint = event->pos();
        if(scribbling == false){
            x = lastPoint.x();
            y = lastPoint.y();
        }
        scribbling = true;
    }

}

void FormsAndCrop::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());

}

void FormsAndCrop::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }

}

void FormsAndCrop::paintEvent(QPaintEvent *event)

{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

}

//void FormsAndCrop::resizeEvent(QResizeEvent *event)
////! [15] //! [16]
//{
//    if (width() > image.width() || height() > image.height()) {
//        int newWidth = qMax(width() + 128, image.width());
//        int newHeight = qMax(height() + 128, image.height());
//        resizeImage(&image, QSize(newWidth, newHeight));

//    }

//}

void FormsAndCrop::drawLineTo(const QPoint &endPoint)

{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    clearImage();
    lastP = lastPoint.x()-x;
    firstP = endPoint.y()-y;
    if(trimSelect == 1 ){
        painter.drawRect(x,y,lastP, firstP);
    }
    else if(trimSelect == 2 ){
        painter.drawEllipse(x,y,lastP, firstP);
    }


    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

//void FormsAndCrop::resizeImage(QImage *image, const QSize &newSize)

//{
//    if (image->size() == newSize)
//        return;

//    QImage newImage(newSize, QImage::Format_ARGB32);
//    newImage.fill(qRgba(0, 0, 0, 0));

//    QPainter painter(&newImage);
//    painter.drawImage(QPoint(0, 0), *image);
//    *image = newImage;
//}
