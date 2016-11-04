#include "menubar.h"

 Menubar:: Menubar(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);

    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Foreground,Qt::red);
    setPalette(*palette);

     for (int i = 0 ; i < 5; i++){
         menuButton[i] = new PushButton(this);
         menuButton[i]->setGeometry((i*49)+1,1,48,48);
         menuButton[i]->setIconSize(QSize(48,48));
     }

    menuButton[0]->setIcon(QPixmap(":/ui/images/armor.png"));
    menuButton[1]->setIcon(QPixmap(":/ui/images/backpack.png"));
    menuButton[2]->setIcon(QPixmap(":/ui/images/spellbook.png"));
    menuButton[3]->setIcon(QPixmap(":/ui/images/map.png"));
    menuButton[4]->setIcon(QPixmap(":/ui/images/setting.png"));
}


void Menubar::resizeMe(QSize newSize){
//    const double scale_factor = (double)32 / (double)1080;
//    double size = newSize.height()*scale_factor;
//    resize(QSize(size,size));
//    setPixmap(origPix.scaled(size,size,Qt::KeepAspectRatio));
}
