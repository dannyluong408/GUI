#include "unitframe.h"

UnitFrame::UnitFrame(QWidget *parent)
    : QFrame(parent)
{
    resize(230,80);
    unitIcon = new QLabel(this);
    health = new QProgressBar(this);
    mana = new QProgressBar(this);

    unitIcon->setGeometry(0,0,80,80);
    health->setGeometry(80,0,150,40);
    mana->setGeometry(80,40,150,40);

    avatar = QPixmap(":/ui/images/panda2.jpg");
    unitIcon->setPixmap(avatar.scaled(80,80,Qt::IgnoreAspectRatio));
    unitIcon->setContentsMargins(0, 0, 0, 0);
    unitIcon->setStyleSheet("border: 1px solid black;");

    health->setRange(0,100);
    health->setValue(50);
    health->setStyleSheet("QProgressBar {"
                          "border: 1px solid grey;"
                          "border-radius: 5px;"
                          "text-align: center;"
                          "}"
                          "QProgressBar::chunk {"
                          "background-color: #FF3333;"
                          "}");
    mana->setRange(0,50);
    mana->setValue(25);
    mana->setAlignment(Qt::AlignCenter);
    mana->setStyleSheet("QProgressBar {"
                          "border: 1px solid grey;"
                          "border-radius: 5px;"
                          "text-align: center;"
                          "}"
                          "QProgressBar::chunk {"
                          "background-color: #2E64FE;"
                          "}");
}

void UnitFrame::resizeMe(QSize newSize){ //todo
//    const double scale_factor = (double)32 / (double)1080;
//    resize(QSize(newSize.height()*scale_factor , newSize.height()*scale_factor));

    const double scale_factor_icon = (double)80 / double(1080);
    const double scale_factor_h = (double)40 / (double)1080;
    const double scale_factor_w = (double)150 / (double)1080;


    //todo fix icon scaling too
    unitIcon->setPixmap(avatar.scaled(newSize.width()*scale_factor_icon,
                                      newSize.height()*scale_factor_icon,
                                      Qt::IgnoreAspectRatio));
//    unitIcon->resize(newSize.width()*scale_factor_icon,newSize.height()*scale_factor_icon);
//    health->resize(newSize.width()*scale_factor_w,newSize.height()*scale_factor_h);
//    mana->resize(newSize.width()*scale_factor_w,newSize.height()*scale_factor_h);
    unitIcon->setGeometry(0,0,
                          newSize.width()*scale_factor_icon,
                          newSize.height()*scale_factor_icon);
    health->setGeometry(newSize.width()*scale_factor_icon,
                        0,
                        newSize.width()*scale_factor_w,
                        newSize.height()*scale_factor_h);
    mana->setGeometry(newSize.width()*scale_factor_icon,
                      newSize.height()*scale_factor_h,
                      newSize.width()*scale_factor_w,
                      newSize.height()*scale_factor_h);

    resize(newSize.width()*scale_factor_icon+
           newSize.width()*scale_factor_w,
           newSize.height()*scale_factor_h*2);

//    health->move(newSize.width()*scale_factor_icon,0);
//    mana->move(newSize.width()*scale_factor_icon,
//               newSize.height()*scale_factor_h);

    //qDebug() << unitIcon->size() << health->size() << mana->size();
}

void UnitFrame::setAvatar(QPixmap newAva){
    avatar = newAva;
}
