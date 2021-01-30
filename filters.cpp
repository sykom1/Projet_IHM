#include "filters.h"

filters::filters()
{

}

 void filters::invertPixel(ImageForChange *image, DisplayContains *displayCont){
    QImage img = image->getActualImg();
    img.invertPixels();
    displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
    image->changeActualImg(img);
}

 void filters::mirroredH(ImageForChange *image, DisplayContains *displayCont){
    displayCont->refreshImage(image->getActualImg().mirrored(true, false), displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
    image->changeActualImg(image->getActualImg().mirrored(true, false));
}

 void filters::mirroredV(ImageForChange *image, DisplayContains *displayCont){
    displayCont->refreshImage(image->getActualImg().mirrored(false, true), displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
    image->changeActualImg(image->getActualImg().mirrored(false, true));
}

 void filters::redFilter(ImageForChange *image, DisplayContains *displayCont){
     QImage img(image->getActualImg());
     for(int y = 0; y < img.height(); y++){
         for(int x = 0; x < img.width(); x++){
             //int red(image->getActualImg().pixelColor(x,y).red());
             int green(image->getActualImg().pixelColor(x,y).green());
             int blue(image->getActualImg().pixelColor(x,y).blue());
             QColor c(255,green,blue);
             img.setPixelColor(x,y,c);
         }
     }
     displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
     image->changeActualImg(img);
 }

 void filters::greenFilter(ImageForChange *image, DisplayContains *displayCont){
     QImage img(image->getActualImg());
     for(int y = 0; y < img.height(); y++){
         for(int x = 0; x < img.width(); x++){
             int red(image->getActualImg().pixelColor(x,y).red());
             //int green(image->getActualImg().pixelColor(x,y).green());
             int blue(image->getActualImg().pixelColor(x,y).blue());
             QColor c(red,255,blue);
             img.setPixelColor(x,y,c);
         }
     }
     displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
     image->changeActualImg(img);
 }

 void filters::blueFilter(ImageForChange * image, DisplayContains *displayCont){
     QImage img(image->getActualImg());
     for(int y = 0; y < img.height(); y++){
         for(int x = 0; x < img.width(); x++){
             int red(image->getActualImg().pixelColor(x,y).red());
             int green(image->getActualImg().pixelColor(x,y).green());
             //int blue(image->getActualImg().pixelColor(x,y).blue());
             QColor c(red,green,255);
             img.setPixelColor(x,y,c);
         }
     }
     displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
     image->changeActualImg(img);
 }

 void filters::sharpenFilter(ImageForChange *image, DisplayContains *displayCont, int red100, int green100, int blue100){
     QImage img(image->getActualImg());
     for(int y = 0; y < img.height(); y++){
         for(int x = 0; x < img.width(); x++){
             int red(image->getActualImg().pixelColor(x,y).red());
             int green(image->getActualImg().pixelColor(x,y).green());
             int blue(image->getActualImg().pixelColor(x,y).blue());

             if(red+red100/100 < 255){
                 red = red+red100/100;
             }
             else{
                 red = 255;
             }
             if(green+green100/100 < 255){
                 green = green+green100/100;
             }
             else{
                 green = 255;
             }
             if(blue+blue100/100 < 255){
                 blue = blue+blue100/100;
             }
             else{
                 blue = 255;
             }

             QColor c(red,green,blue);
             img.setPixelColor(x,y,c);
         }
     }
     displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
     image->changeActualImg(img);
 }





