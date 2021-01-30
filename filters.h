#ifndef FILTERS_H
#define FILTERS_H


#include <iostream>
#include "imageforchange.h"
#include "displaycontains.h"


class filters
{
public:
    filters();


    static void invertPixel(ImageForChange *image, DisplayContains *displayCont);
    static void mirroredH(ImageForChange *image, DisplayContains *displayCont);
    static void mirroredV(ImageForChange *image, DisplayContains *displayCont);
    static void redFilter(ImageForChange *image, DisplayContains *displayCont);
    static void greenFilter(ImageForChange *image, DisplayContains *displayCont);
    static void blueFilter(ImageForChange *image, DisplayContains *displayCont);
    static void sharpenFilter(ImageForChange *image, DisplayContains *displayCont, int red100, int green100, int blue100);


};

#endif // FILTERS_H
