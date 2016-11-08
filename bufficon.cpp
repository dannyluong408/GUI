#include "bufficon.h"


BuffIcon::BuffIcon(QWidget *parent)
    : QLabel(parent)
{
    resize(24,24);
    buffID = 0;
}

void BuffIcon::resizeMe(QSize newSize){
    const double scale_factor = (double)24 / (double)1080;
    double size = newSize.height()*scale_factor;
    resize(QSize(size,size));
    setPixmap(origPix.scaled(size,size,Qt::KeepAspectRatio));
}



void BuffIcon::setOGPix(const QPixmap *ogPix){
   origPix = *ogPix;
}

void BuffIcon::setBuffDuration(uint64_t time){
    end_time = time;
}

uint64_t BuffIcon::getBuffDuration() const{
    return end_time;
}
