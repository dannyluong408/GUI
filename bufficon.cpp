#include "bufficon.h"


BuffIcon::BuffIcon(QWidget *parent)
    : QLabel(parent)
{
}

void BuffIcon::resizeMe(QSize newSize){
    const double scale_factor = (double)32 / (double)1080;
    resize(QSize(newSize.height()*scale_factor , newSize.height()*scale_factor));
    setPixmap(origPix.scaled(newSize.height()*scale_factor,
                               newSize.height()*scale_factor,Qt::KeepAspectRatio));
}

void BuffIcon::setOGPix(const QPixmap *ogPix){
   origPix = *ogPix;
}
