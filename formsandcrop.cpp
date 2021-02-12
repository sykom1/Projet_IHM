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
                           DisplayContains *displayContains, ImageForChange *imgForChange,QPushButton *crop, QPushButton *del,QAction *cropAction, QAction *delAction): QWidget()
{
    this->trimSelect = trimSelect;
    this->scroll = scrollArea;
    this->displayContains = displayContains;
    this->imgForChange = imgForChange;
    this->newImage = newImage;
    this->crop=crop;
    this->del=del;
    this->cropAction=cropAction;
    this->delAction=delAction;

    xScroll = x;
    yScroll = y;
    heightSave = height;
    widthSave = width;

    pictureArea();
}


void FormsAndCrop::clearImage()

{
    image.convertToFormat(QImage::Format_ARGB32);
    image.fill(qRgba(255,255,255,0));

    modified = true;
    update();
}

void FormsAndCrop::initCrop(){
    xCrop = 0;
    yCrop = 0;
}

void FormsAndCrop::mousePressEvent(QMouseEvent *event)

{

    if (event->button() == Qt::LeftButton) {

        lastPoint = event->pos();
        if(scribbling == false){
            x = lastPoint.x();
            y = lastPoint.y();

            crop->setEnabled(false);
            crop->setVisible(false);
            del->setEnabled(false);
            del->setVisible(false);
            cropAction->setEnabled(false);
            delAction->setEnabled(false);

        }
        scribbling = true;
    }

}

void FormsAndCrop::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling){
        drawLineTo(event->pos());
        drawFormTo(event->pos());
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

    if(lastP!=firstP){
        crop->setEnabled(true);
        crop->setVisible(true);
        del->setEnabled(true);
        del->setVisible(true);
        cropAction->setEnabled(true);
        cropAction->setVisible(true);
        delAction->setEnabled(true);
        delAction->setVisible(true);
    }

    if(trimSelect == 1 ){



        if(lastP<0){
            if(x+lastP <0){
                lastP = -x;
            }
        }
        if(firstP<0){
            if(y+firstP <0){
                firstP = -y;
            }
        }
        if(firstP >imgForChange->getActualImg().height()){
            firstP =imgForChange->getActualImg().height()-y;
        }

        if(lastP >imgForChange->getActualImg().width()){
            lastP =imgForChange->getActualImg().width()-x;
        }

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

        painter.drawLine(lastPoint, change);
        modified = true;
        lastPoint = change;
        displayContains->refreshImage(img, xCrop, yCrop);
        imgForChange->changeActualImg(img);
        displayContains->changeSizeOfScrollBar(widthSave, heightSave);

    }




}

QImage FormsAndCrop::doTrim(QImage img, int trimSelect, QLabel* labelForImage){

        QRect rect(x,y,lastP,firstP );
        rect= rect.normalized();

        if(trimSelect== 1){
            img = img.copy(rect );

        }
        else if(trimSelect == 2){

            QPixmap target = QPixmap(size());
            target.fill(Qt::transparent);

            QPixmap p = QPixmap::fromImage(img);


            QPainter painter (&target);

            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

            QPainterPath path = QPainterPath();
            path.addEllipse(rect);

            painter.setClipPath(path);
            painter.drawPixmap(0, 0, p);
            labelForImage->setPixmap(target);
            img = target.toImage();      
            img = img.copy(rect );


        }

        clearImage();
        displayContains->refreshImage(img, displayContains->getScrollArea()->x(), displayContains->getScrollArea()->y());
        displayContainsCrop(x,y,lastP,firstP);
        imgForChange->changeActualImg(img);




        pictureArea();
        return img;


}

void FormsAndCrop::zoom(ImageForChange *image, DisplayContains *displCont){
    QImage img = image->getActualImg();
    img = img.scaledToWidth(1500, Qt::FastTransformation);
    image->changeActualImg(img);
    displCont->refreshImage(image->getActualImg(), displCont->getScrollArea()->x(), displCont->getScrollArea()->y());
    std::cout << "rentrer dans la fonction filtre" << std::endl;
}

void FormsAndCrop::dezoom(ImageForChange *image, DisplayContains *displCont){
    QImage img = image->getActualImg();
    img = img.scaledToWidth(100, Qt::FastTransformation);
    image->changeActualImg(img);
    displCont->refreshImage(image->getActualImg(), displCont->getScrollArea()->x(), displCont->getScrollArea()->y());
}


void FormsAndCrop::pictureArea(){
    QImage tempoImg = imgForChange->getActualImg();
    QImage newImage(QSize(tempoImg.width(), tempoImg.height()), QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0, 0, 0));

    QPainter painter(&newImage);
    image = newImage;
    this->move(xCrop+xScroll, yCrop+yScroll);
    this->setFixedWidth(tempoImg.width());
    this->setFixedHeight(tempoImg.height());
}


void FormsAndCrop::displayContainsCrop(int x,int y,int lastP, int firstP){
    if(lastP > 0 && firstP >0){
        displayContains->moveScrollArea(x + xCrop, y+ yCrop);
        xCrop += x;
        yCrop += y;
    }
    else if(lastP < 0 && firstP >0){
        displayContains->moveScrollArea(x+lastP+xCrop, y+yCrop);

        xCrop += x +lastP;
        yCrop += y;
    }
    else if(lastP > 0 && firstP <0){
        displayContains->moveScrollArea(x+xCrop, y+firstP+yCrop);
        xCrop += x;
        yCrop += y+firstP;
    }
    else if(lastP < 0 && firstP <0){
        displayContains->moveScrollArea(x+lastP+xCrop, y+firstP+yCrop);
        xCrop += x+lastP;
        yCrop += y+firstP;
    }
}




