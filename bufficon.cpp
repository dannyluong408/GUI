#include "bufficon.h"


BuffIcon::BuffIcon(QWidget *parent)
    : QLabel(parent)
{
}

void BuffIcon::resizeMe(QSize newSize){
    const double scale_factor = (double)32 / (double)1080;
    double size = newSize.height()*scale_factor;
    resize(QSize(size,size));
    setPixmap(origPix.scaled(size,size,Qt::KeepAspectRatio));
}

void BuffIcon::setOGPix(const QPixmap *ogPix){
   origPix = *ogPix;
}
