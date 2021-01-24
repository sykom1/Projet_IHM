#include "filters.h"

filters::filters()
{

}

 void filters::invertPixel(ImageForChange *image, DisplayContains *displayCont){
    QImage img = image->getActualImg();
    img.invertPixels();
    image->changeActualImg(img);
    displayCont->refreshImage(image->getActualImg());
}

 void filters::mirroredH(ImageForChange *image, DisplayContains *displayCont){
    image->changeActualImg(image->getActualImg().mirrored(true, false));
    displayCont->refreshImage(image->getActualImg());
}

 void filters::mirroredV(ImageForChange *image, DisplayContains *displayCont){
    image->changeActualImg(image->getActualImg().mirrored(false, true));
    displayCont->refreshImage(image->getActualImg());
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
     image->changeActualImg(img);
     displayCont->refreshImage(image->getActualImg());
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
     image->changeActualImg(img);
     displayCont->refreshImage(image->getActualImg());
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
     image->changeActualImg(img);
     displayCont->refreshImage(image->getActualImg());
 }





