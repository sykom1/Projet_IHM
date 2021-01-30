#include "colorparameter.h"

colorParameter::colorParameter(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Reglage couleurs"));
    setupUi(this);
}
