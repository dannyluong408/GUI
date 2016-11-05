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
         menuButton[i]->setGeometry((i*48),0,48,48);
         menuButton[i]->setIconSize(QSize(48,48));
     }

    menuButton[0]->setIcon(QPixmap(":/ui/images/armor.png"));
    menuButton[1]->setIcon(QPixmap(":/ui/images/backpack.png"));
    menuButton[2]->setIcon(QPixmap(":/ui/images/spellbook.png"));
    menuButton[3]->setIcon(QPixmap(":/ui/images/map.png"));
    menuButton[4]->setIcon(QPixmap(":/ui/images/setting.png"));
}

void Menubar::resizeMe(QSize newSize){ //lol what a mess fix for 1080p resolution later
    const double scale_factor_x = (double)950 / (double)1200;
    const double scale_factor_y = (double)800 / (double)900;
    const double scale_factor_w = (double)240 / (double)1200;
    const double scale_factor_h = (double)48 / (double)900;
    const double scale_factor_spacing = (double)48 / (double)1200;
    const double icon_size = newSize.height()*scale_factor_h;

    resize(newSize.width()*scale_factor_w,newSize.height()*scale_factor_h);
    move(newSize.width()*scale_factor_x,newSize.height()*scale_factor_y);

    for(int i = 0; i<5; i++){
        menuButton[i]->move(i*(scale_factor_spacing*newSize.width()),0);
        menuButton[i]->resize(icon_size,icon_size);
    }

    menuButton[0]->setIcon(QPixmap(":/ui/images/armor.png").scaled(icon_size,icon_size,Qt::KeepAspectRatio));
    menuButton[1]->setIcon(QPixmap(":/ui/images/backpack.png").scaled(icon_size,icon_size,Qt::KeepAspectRatio));
    menuButton[2]->setIcon(QPixmap(":/ui/images/spellbook.png").scaled(icon_size,icon_size,Qt::KeepAspectRatio));
    menuButton[3]->setIcon(QPixmap(":/ui/images/map.png").scaled(icon_size,icon_size,Qt::KeepAspectRatio));
    menuButton[4]->setIcon(QPixmap(":/ui/images/setting.png").scaled(icon_size,icon_size,Qt::KeepAspectRatio));
}
