#include "colorparameter.h"

mainWindowMenu *mainWindMen;

colorParameter::colorParameter(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Reglage couleurs"));
    setupUi(this);

    //connect(accept_Button, &QPushButton::clicked,this,&colorParameter::colorChanged);
    connect(redSlider, &QSlider::actionTriggered,this,&colorParameter::colorChanged);
    connect(greenSlider, &QSlider::actionTriggered,this,&colorParameter::colorChanged);
    connect(blueSlider, &QSlider::actionTriggered,this,&colorParameter::colorChanged);

}

colorParameter::colorParameter(ImageForChange* imgForChange,DisplayContains* dispCont, QImage annulImg, QWidget *parent) :
    QDialog(parent)
{
    this->displayContains = dispCont;
    this->imgForChange = imgForChange;
    this->annulImg = annulImg;
    setWindowTitle(tr("Reglage couleurs"));
    setupUi(this);

    connect(redSlider, &QSlider::actionTriggered,this,&colorParameter::colorChanged);
    connect(greenSlider, &QSlider::actionTriggered,this,&colorParameter::colorChanged);
    connect(blueSlider, &QSlider::actionTriggered,this,&colorParameter::colorChanged);
    connect(refuse_Button, &QPushButton::clicked,this,&colorParameter::annulButton);


}

void colorParameter::colorChanged(){
    filters::sharpenFilter(this->imgForChange,this->displayContains,redSlider->value(),greenSlider->value(),blueSlider->value());
}

void colorParameter::on_redValueLabel_windowIconTextChanged(const QString &iconText){

}

void colorParameter::annulButton(){
    imgForChange->changeActualImg(annulImg);
    displayContains->refreshImage(imgForChange->getActualImg(), displayContains->getScrollArea()->x(), displayContains->getScrollArea()->y());
}

