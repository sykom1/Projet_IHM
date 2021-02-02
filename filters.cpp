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
             if(img.pixel(x,y) != 0){
                 //int red(image->getActualImg().pixelColor(x,y).red());
                 int green(image->getActualImg().pixelColor(x,y).green());
                 int blue(image->getActualImg().pixelColor(x,y).blue());
                 QColor c(255,green,blue);
                 img.setPixelColor(x,y,c);
             }
         }
     }
     displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
     image->changeActualImg(img);
 }

 void filters::greenFilter(ImageForChange *image, DisplayContains *displayCont){
     QImage img(image->getActualImg());
     for(int y = 0; y < img.height(); y++){
         for(int x = 0; x < img.width(); x++){
             if(img.pixel(x,y) != 0){
                 int red(image->getActualImg().pixelColor(x,y).red());
                 //int green(image->getActualImg().pixelColor(x,y).green());
                 int blue(image->getActualImg().pixelColor(x,y).blue());
                 QColor c(red,255,blue);
                 img.setPixelColor(x,y,c);
             }
         }
     }
     displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
     image->changeActualImg(img);
 }

 void filters::blueFilter(ImageForChange * image, DisplayContains *displayCont){
     QImage img(image->getActualImg());
     for(int y = 0; y < img.height(); y++){
         for(int x = 0; x < img.width(); x++){
             if(img.pixel(x,y) != 0){
                 int red(image->getActualImg().pixelColor(x,y).red());
                 int green(image->getActualImg().pixelColor(x,y).green());
                 //int blue(image->getActualImg().pixelColor(x,y).blue());
                 QColor c(red,green,255);
                 img.setPixelColor(x,y,c);
             }
         }
     }
     displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
     image->changeActualImg(img);
 }

 void filters::sharpenFilter(ImageForChange *image, DisplayContains *displayCont, int red100, int green100, int blue100){
//     std::cout << "Valeur Rouge : " << red100 << std::endl;
//     std::cout << "Valeur Verte : " << green100 << std::endl;
//     std::cout << "Valeur Bleue : " << blue100 << std::endl;

     QImage img(image->getActualImg());
     for(int y = 0; y < img.height(); y++){
         for(int x = 0; x < img.width(); x++){

             if(img.pixel(x,y) != 0){

                 int red(image->getFiltersImg().pixelColor(x,y).red());
                 int green(image->getFiltersImg().pixelColor(x,y).green());
                 int blue(image->getFiltersImg().pixelColor(x,y).blue());

                 int newRed;
                 int newGreen;
                 int newBlue;

                 if(red+255*red100/100 < 255){
                     newRed = red+red*red100/100;
                 }
                 else{
                     newRed = 255;
                 }


                 if(green+255*green100/100 < 255){
                     newGreen = green+green*green100/100;
                 }
                 else{
                     newGreen = 255;
                 }
                 if(blue+255*blue100/100 < 255){
                     newBlue = blue+blue*blue100/100;
                 }
                 else{
                     newBlue = 255;
                 }

                 QColor c(newRed,newGreen,newBlue);
                 img.setPixelColor(x,y,c);
             }
         }
     }
     image->changeActualImg(img);
     displayCont->refreshImage(img, displayCont->getScrollArea()->x(), displayCont->getScrollArea()->y());
 }





