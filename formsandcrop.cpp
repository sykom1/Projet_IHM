#include "formsandcrop.h"
#include "drawcolormenu.h"
#include <QMouseEvent>
#include <QPainter>
#include <QtWidgets>

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

int FormsAndCrop::xCrop;
int FormsAndCrop::yCrop;
FormsAndCrop::FormsAndCrop(int x, int y, int height, int width,int trimSelect, QScrollArea *scrollArea,
                           DisplayContains *displayContains, ImageForChange *imgForChange): QWidget()
{


    //    QImage tempoImg = imgForChange->getActualImg();
    //    QImage newImage(QSize(tempoImg.width(), tempoImg.height()), QImage::Format_ARGB32);


    //    qInfo()<<"AAAAA";
    //    qInfo()<<tempoImg.width()<<" "<<tempoImg.height()<<"\n\n";
    //    newImage.fill(qRgba(0, 0, 0, 0));

    //    QPainter painter(&newImage);

    //    //painter.drawImage(QPoint(0, 0), image);
    //    image = newImage;
    //    this->move(x, y);
    //    this->setFixedWidth(width);
    //    this->setFixedHeight(height);
    this->trimSelect = trimSelect;
    this->scroll = scrollArea;
    this->displayContains = displayContains;
    this->imgForChange = imgForChange;
    this->newImage = newImage;

    xScroll = x;
    yScroll = y;

    pictureArea();
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
    if ((event->buttons() & Qt::LeftButton) && scribbling){
        drawLineTo(event->pos());
        drawFormTo(event->pos());
//        if(event->x()>=scroll->width()-scroll->width()*0.1){
//            float value = (float)(scroll->horizontalScrollBar()->value()*0.1);
//            if(value>=0 && value <1)
//                value=1;
//            scroll->horizontalScrollBar()->setValue(scroll->horizontalScrollBar()->value()+value);
//        }
//        if(event->y()>=scroll->height()-scroll->height()*0.1){
//            float value = (float)(scroll->verticalScrollBar()->value()*0.1);
//            if(value>=0 && value <1){
//                value = 1;
//            }
//            scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->value()+value);
//            std::cout << value << std::endl;
//        }
    }

}

void FormsAndCrop::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {


        drawFormTo(event->pos());

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


void FormsAndCrop::drawFormTo(const QPoint &endPoint)

{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    lastP = lastPoint.x()-x;
    firstP = endPoint.y()-y;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    if(trimSelect == 1 ){
        clearImage();
        painter.drawRect(x,y,lastP, firstP);
        painter.fillRect(x,y,lastP, firstP,QBrush(QColor(199, 225, 246, 127)));
    }
    else if(trimSelect == 2 ){
        clearImage();
        painter.setBrush(QBrush(QColor(199, 225, 246, 127)));
        painter.drawEllipse(x,y,lastP, firstP);
    }



    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}



void FormsAndCrop::drawLineTo(const QPoint &endPoint){


    if(trimSelect == 3 ){




        myPenColor = drawColorMenu().colorStat;
        QImage img =  imgForChange->getActualImg();
        QPainter painter (&img);
        painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));

        QPoint change = endPoint;
//        change.setY(endPoint.y()-yCrop);
//        change.setX(endPoint.x()-xCrop);
//        lastPoint.setY(lastPoint.y()-yCrop);
//        lastPoint.setX(lastPoint.x()-xCrop);

        painter.drawLine(lastPoint, change);
        modified = true;
        lastPoint = change;
        imgForChange->changeActualImg(img);
        displayContains->refreshImage(imgForChange->getActualImg());


        displayContains->moveScrollArea(xCrop, yCrop);

    }




}

QImage FormsAndCrop::doTrim(QImage img, int trimSelect, QLabel* labelForImage){



        if(trimSelect== 1){
            img = img.copy(x,y,lastP,firstP );




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
           // path.addRoundedRect(x,y, lastP,firstP, 50, 50);
            path.addEllipse(x,y, lastP,firstP);

            painter.setClipPath(path);
            painter.drawPixmap(0, 0, p);
            labelForImage->setPixmap(target);
            img = target.toImage();



        }


        clearImage();
        imgForChange->changeActualImg(img);
        displayContains->refreshImage(imgForChange->getActualImg());

        if(trimSelect ==1){

            displayContains->moveScrollArea(x + xCrop, y+ yCrop);
        }else if(trimSelect == 2){
             //displayContains->moveScrollArea(-xCrop, -yCrop);
        }
        xCrop += x;
        yCrop += y;
        //this->move(x, y);


        //displayContains->moveScrollArea(0, 0);
       // pictureArea();
        return img;


}

void FormsAndCrop::zoom(ImageForChange *image, DisplayContains *displCont){
    QImage img = image->getActualImg();
    img = img.scaledToWidth(1500, Qt::FastTransformation);
    image->changeActualImg(img);
    //imageForChange->getActualImg().invertPixels();
    displCont->refreshImage(image->getActualImg());
    //img.setOffset(QPoint(500,200)); // ne fonctionne pas
    std::cout << "rentrer dans la fonction filtre" << std::endl;
}


void FormsAndCrop::pictureArea(){
    QImage tempoImg = imgForChange->getActualImg();
    QImage newImage(QSize(tempoImg.width(), tempoImg.height()), QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0, 0, 0));

    QPainter painter(&newImage);

    //painter.drawImage(QPoint(0, 0), image);
    image = newImage;
    this->move(xCrop+xScroll, yCrop+yScroll);
    this->setFixedWidth(tempoImg.width());
    this->setFixedHeight(tempoImg.height());
}





