#include "unitframe.h"


UnitFrame::UnitFrame(QWidget *parent)
    : QFrame(parent)
{
    resize(260,100);
    unitIcon = new QLabel(this);
    health = new QProgressBar(this);
    mana = new QProgressBar(this);
    name = new QLabel(this);
    setStyleSheet("border: 1px solid black;");

    name->setGeometry(100,0,160,20);
    unitName = "Gamer";
    name->setText(unitName);
    name->setAlignment(Qt::AlignCenter);

    unitIcon->setGeometry(0,0,100,100);
    health->setGeometry(100,20,160,40);
    mana->setGeometry(100,60,160,40);



    avatar = QPixmap(":/ui/images/oldguy.ico");
    unitIcon->setPixmap(avatar.scaled(100,100,Qt::IgnoreAspectRatio));
    unitIcon->setContentsMargins(1, 1, 1, 1);
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
    partyScale = 1;
    isParty = false;
}

void UnitFrame::setIsParty(bool party){
    isParty = party;
}

void UnitFrame::setScale(double scale){
    partyScale = scale;
}

void UnitFrame::resizeMe(QSize newSize){ //todo
    double scale_factor_icon;
    double scale_factor_h;
    double scale_factor_name_h;
    double scale_factor_w;
    double scale_factor_mana_y;
    double sf_frame_w;
    double sf_frame_h;


    if(!isParty){
        scale_factor_icon = 100.0 / 900.0;
        scale_factor_h = 40.0 / 900.0;
        scale_factor_name_h = 20.0 / 900.0;
        scale_factor_w = 160.0 / 900.0;
        scale_factor_mana_y = 60.0 / 900.0;
        sf_frame_w = 262.0 / 900.0;
        sf_frame_h = 100.0 / 900.0;

        //todo fix icon scaling too
        unitIcon->setPixmap(avatar.scaled(newSize.height()*scale_factor_icon,
                                          newSize.height()*scale_factor_icon,
                                          Qt::IgnoreAspectRatio));

        name->setGeometry(newSize.height()*scale_factor_icon,
                          0,
                          newSize.height()*scale_factor_w,
                          newSize.height()*scale_factor_name_h);

        unitIcon->setGeometry(0,0,
                              newSize.height()*scale_factor_icon,
                              newSize.height()*scale_factor_icon);
        health->setGeometry(newSize.height()*scale_factor_icon,
                            newSize.height()*scale_factor_name_h,
                            newSize.height()*scale_factor_w,
                            newSize.height()*scale_factor_h);
        mana->setGeometry(newSize.height()*scale_factor_icon,
                          newSize.height()*scale_factor_mana_y,
                          newSize.height()*scale_factor_w,
                          newSize.height()*scale_factor_h);

        resize(newSize.height()*sf_frame_w,
              newSize.height()*sf_frame_h);
    }
    else{
        scale_factor_icon = (100.0 * partyScale)/ 900.0;
        scale_factor_h = (40.0 * partyScale)/ 900.0;
        scale_factor_name_h = (20.0* partyScale) / 900.0;
        scale_factor_w = (160.0* partyScale) / 900.0;
        scale_factor_mana_y = (60.0* partyScale) / 900.0;
        sf_frame_w = (262.0 * partyScale)/ 900.0;
        sf_frame_h = (100.0 * partyScale)/ 900.0;

        //todo fix icon scaling too
        unitIcon->setPixmap(avatar.scaled(newSize.height()*scale_factor_icon,
                                          newSize.height()*scale_factor_icon,
                                          Qt::IgnoreAspectRatio));

        name->setGeometry(newSize.height()*scale_factor_icon,
                          0,
                          newSize.height()*scale_factor_w,
                          newSize.height()*scale_factor_name_h);

        unitIcon->setGeometry(0,0,
                              newSize.height()*scale_factor_icon,
                              newSize.height()*scale_factor_icon);
        health->setGeometry(newSize.height()*scale_factor_icon,
                            newSize.height()*scale_factor_name_h,
                            newSize.height()*scale_factor_w,
                            newSize.height()*scale_factor_h);
        mana->setGeometry(newSize.height()*scale_factor_icon,
                          newSize.height()*scale_factor_mana_y,
                          newSize.height()*scale_factor_w,
                          newSize.height()*scale_factor_h);

        resize(newSize.height()*sf_frame_w,
              newSize.height()*sf_frame_h);
    }

    return;
}

void UnitFrame::setAvatar(QPixmap newAva){
    avatar = newAva;
}
