#include "bufficon.h"


BuffIcon::BuffIcon(QWidget *parent)
    : QLabel(parent)
{
    setBaseSize(25,25);
    resize(25,25);
    buffID = 0;
    isPlayer = false;
}

QSize BuffIcon::sizeHint() const{
    if (!isPlayer){ //target size
        return QSize(25,25);
    }
    else{ //player size
        return QSize(41,41);
    }
}
void BuffIcon::resizeMe(QSize newSize){
    const double minSize = 900.0;
    double square_icon;
    if (!isPlayer){ //target size
        square_icon = 24.0 / minSize;
    }
    else{ //player size
        square_icon = 41.0 / minSize;

    }
    resize(newSize.height()*square_icon,
           newSize.height()*square_icon);
//    setPixmap(origPix.scaled(newSize.height()*square_icon,
//                             newSize.height()*square_icon,
//                             Qt::KeepAspectRatio));
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
