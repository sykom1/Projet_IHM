#include "filters.h"

filters::filters()
{

}

 void filters::invertPixel(ImageForChange *image, DisplayContains *displayCont){
    QImage img = image->getActualImg();
    img.invertPixels();
    image->changeActualImg(img);
    //imageForChange->getActualImg().invertPixels();
    displayCont->refreshImage(image->getActualImg());
    std::cout << "rentrer dans la fonction filtre" << std::endl;
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

     std::cout << "Value avant :" << image->getActualImg().pixelColor(36,10).red() << std::endl ;
     for(int x = 0; x < image->getActualImg().width(); x++){
         for(int y = 0; y < image->getActualImg().height(); y++){
             QRgb color;
             color = qRgb(150,150,150);
             image->getActualImg().setPixel(x,y,color);
             displayCont->refreshImage(image->getActualImg());
         }
     }

     std::cout << "Value apres :" << image->getActualImg().pixelColor(36,10).red() << std::endl ;
 }

 void filters::greenFilter(ImageForChange *image, DisplayContains *displayCont){
     for(int x = 0; x < image->getActualImg().width(); x++){
         for(int y = 0; y < image->getActualImg().height(); y++){
             if(image->getActualImg().pixelColor(x,y).green() < 255-40){
                 //std::cout << "added" << std::endl;
                 QRgb color = qRgb(image->getActualImg().pixelColor(x,y).red(),image->getActualImg().pixelColor(x,y).green()+40,image->getActualImg().pixelColor(x,y).blue());
                 image->getActualImg().setPixel(x,y,color);
             }
             else{
//                 std::cout << "skipped" << std::endl;
                 QRgb color = qRgb(image->getActualImg().pixelColor(x,y).red(),255,image->getActualImg().pixelColor(x,y).blue());
                 image->getActualImg().setPixel(x,y,color);
             }
         }
     }
     displayCont->refreshImage(image->getActualImg());
 }

 void filters::blueFilter(ImageForChange * image, DisplayContains *displayCont){
     std::cout << "Value avant :" << image->getActualImg().pixelColor(36,10).red() << std::endl ;
     QImage img = QImage(image->getInitImg().width(),image->getActualImg().height(), QImage::Format_RGBX64);
//     for(int x = 0; x < image->getActualImg().width(); x++){
//         for(int y = 0; y < image->getActualImg().height(); y++){
//            img.setPixel(x,y,qRgb(image->getActualImg().pixelColor(x,y).red(),255,image->getActualImg().pixelColor(x,y).blue()));
//         }
//     }
     image->getActualImg().fill(image->getActualImg().pixel(36,10));
     std::cout << "Value après :" << image->getActualImg().pixelColor(0,0).red() << std::endl ;
     displayCont->refreshImage(image->getActualImg());
 }






