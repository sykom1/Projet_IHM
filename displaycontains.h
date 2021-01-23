#ifndef DISPLAYCONTAINS_H
#define DISPLAYCONTAINS_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QScrollBar>
#include <iostream>

class DisplayContains : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayContains(QWidget *parent = nullptr, int heightForScrollArea=0,
                             int initX = 0, int initY = 0);
    void createNewReducedLabel(QImage reduceImage);
    void removeParentForReducedLabel();
    void setVisibleReducedLabel(bool value);
    void setSizeReducedLabel(int height, int width);
    void refreshReducedImage(QImage reducedImage);
    void refreshImage(QImage img);
    bool reducedLabelIsNull();
    void moveReducedLabel(int x, int y);
    void clearDisplay();
    QLabel* getLabelForImage();
    void moveScrollArea(int x, int y);
    QScrollArea* getScrollArea();
    void changeSizeOfScrollBar(int width, int height);
    int getWidthScrollBarArea();
    int getHeightScrollBarArea();

private:
    QScrollArea *scrollAreaForImage;
    QLabel *labelForImage;
    QLabel *labelForReduceImage = nullptr;
    int heightForScrollArea = 0;
    int initX;
    int initY;
    void initSize();

};

#endif // DISPLAYCONTAINS_H
