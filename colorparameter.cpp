#include "colorparameter.h"

mainWindowMenu *mainWindMen;

colorParameter::colorParameter(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Reglage couleurs"));
    setupUi(this);

    connect(accept_Button, &QPushButton::clicked,this,&colorParameter::colorChanged);
}

colorParameter::colorParameter(ImageForChange* imgForChange,DisplayContains* dispCont, QWidget *parent) :
    QDialog(parent)
{
    this->displayContains = dispCont;
    this->imgForChange = imgForChange;
    setWindowTitle(tr("Reglage couleurs"));
    setupUi(this);

    connect(accept_Button, &QPushButton::clicked,this,&colorParameter::colorChanged);


}

void colorParameter::colorChanged(){
    filters::sharpenFilter(this->imgForChange,this->displayContains,redSlider->value(),greenSlider->value(),blueSlider->value());
}

void colorParameter::on_redValueLabel_windowIconTextChanged(const QString &iconText){

}

