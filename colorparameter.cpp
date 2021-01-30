#include "colorparameter.h"

colorParameter::colorParameter(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Reglage couleurs"));
    setupUi(this);

    connect(redSlider, &QSlider::valueChanged,this,&colorParameter::colorChanged);
    connect(greenSlider, &QSlider::valueChanged,this,&colorParameter::colorChanged);
    connect(blueSlider, &QSlider::valueChanged,this,&colorParameter::colorChanged);

}

colorParameter::colorParameter(mainWindowMenu *mainWindMen, QWidget *parent) :
    QDialog(parent)
{
    this->mainWindMen = mainWindMen;
    setWindowTitle(tr("Reglage couleurs"));
    setupUi(this);

    connect(redSlider, &QSlider::valueChanged,this,&colorParameter::colorChanged);
    connect(greenSlider, &QSlider::valueChanged,this,&colorParameter::colorChanged);
    connect(blueSlider, &QSlider::valueChanged,this,&colorParameter::colorChanged);

}

void colorChanged(){
//    filters::sharpenFilter(mainWindMen.get)

}

void colorParameter::on_redValueLabel_windowIconTextChanged(const QString &iconText){

}

