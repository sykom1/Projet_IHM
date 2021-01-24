#ifndef CHOSECOLOR_H
#define CHOSECOLOR_H

#include <QDialog>
#include <QMainWindow>
#include <QFileDialog>
#include <QImageReader>
#include <QScrollArea>
#include <QLabel>
#include <iostream>
#include <QPainter>
#include <QMainWindow>
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPainterPath>
#include <QPainter>
#include <QtWidgets>


namespace Ui {
class choseColor;
}

class choseColor : public QDialog
{
    Q_OBJECT

public:
    explicit choseColor(QWidget *parent = nullptr);
    ~choseColor();
     QColor color;


private:
    Ui::choseColor *ui;
    void createColorMenu();
    void runEvents();
    QPushButton *m_button;
    void handleButton();


};

#endif // CHOSECOLOR_H
