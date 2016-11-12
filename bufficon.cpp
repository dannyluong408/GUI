#include "bufficon.h"


BuffIcon::BuffIcon(QWidget *parent)
    : QLabel(parent)
{
    resize(25,25);
    buffID = 0;
    isPlayer = false;
}

void BuffIcon::resizeMe(QSize newSize){
    double scale_factor_w = (double)25/ (double)1200;
    double scale_factor_h = (double)25/ (double)900;
    if (!isPlayer){ //target size
        resize(newSize.width()*scale_factor_w,
               newSize.height()*scale_factor_h);
        setPixmap(origPix.scaled(newSize.width()*scale_factor_w,
                                 newSize.height()*scale_factor_h,
                                 Qt::KeepAspectRatio));
    }
    else{ //player size
        scale_factor_w = (double)42 / (double)1200;
        scale_factor_h = (double)42 / (double)900;
        resize(newSize.width()*scale_factor_w,
               newSize.height()*scale_factor_h);
        setPixmap(origPix.scaled(newSize.width()*scale_factor_w,
                                 newSize.height()*scale_factor_h,
                                 Qt::KeepAspectRatio));
    }
}


void BuffIcon::setIsPlayer(bool player){
    isPlayer = player;
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
