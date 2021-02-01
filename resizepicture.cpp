#include "resizepicture.h"
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>


resizePicture::resizePicture(QWidget *parent) : QWidget(parent)
{

}





QImage resizePicture::resize(QImage image, int x, int y){
   return image.scaled(x,y,Qt::KeepAspectRatioByExpanding);
}
