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

