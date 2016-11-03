#include "buffframe.h"


BuffFrame::BuffFrame(QWidget *parent)
    : QFrame(parent)
{

}

void BuffFrame::resizeMe(QSize newSize){
    const double scale_factor = (double)32 / (double)1080;
    resize(QSize(newSize.height()*scale_factor , newSize.height()*scale_factor));
    const int minsize = (newSize.height() > newSize.width()) ? newSize.width() : newSize.height();
    //reposition here
    int count = 0;
    for(BuffIcon* i: buffs){
       i->move(QPoint(scale_factor*minsize*count,100*scale_factor));
       count++;
    }

}

void BuffFrame::insertBuff(BuffIcon* buff){
    buffs.push_back(buff);
}

//void removeBuff(int spellid){
//    auto i = buffs.start();
//    while (i != buffs.end()) {

//        buffs.erase(i);

//    }
//}
