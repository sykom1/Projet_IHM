#ifndef RESIZEPICTURE_H
#define RESIZEPICTURE_H

#include <QWidget>

class resizePicture : public QWidget
{
    Q_OBJECT
public:
    explicit resizePicture(QWidget *parent = nullptr);
    QImage resize(QImage img, int x, int y);

signals:

};

#endif // RESIZEPICTURE_H
