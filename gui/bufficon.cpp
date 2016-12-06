#include "GUI/bufficon.h"

BuffIcon::BuffIcon(QWidget *parent)
    : QLabel(parent)
{
    buffID = 0;
    isPlayer = false;
}

QSize BuffIcon::sizeHint() const{
    if (!isPlayer){ //target size
        return QSize(25.0,25.0);
    }
    else{ //player size
        return QSize(42.0,42.0);
    }
}
void BuffIcon::resizeMe(QSize newSize){
    const double minSize = 900.0;
    double square_icon;
    if (!isPlayer){ //target size
        square_icon = 25.0 / minSize;
    }
    else{ //player size
        square_icon = 42.0 / minSize;

    }
    resize(newSize.height()*square_icon,
           newSize.height()*square_icon);
}

bool BuffIcon::getIsPlayer(){
  return isPlayer;
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
