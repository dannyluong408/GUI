#include "unitframe.h"

UnitFrame::UnitFrame(QWidget *parent)
    : QFrame(parent)
{
    resize(250,100);
    unitIcon = new QLabel(this);
    health = new QProgressBar(this);
    mana = new QProgressBar(this);
    name = new QLabel(this);
    setStyleSheet("border: 1px solid black;");

    name->setGeometry(100,0,150,20);
    unitName = "Gamer";
    name->setText(unitName);
    name->setAlignment(Qt::AlignCenter);

    unitIcon->setGeometry(0,0,100,100);
    health->setGeometry(100,20,150,40);
    mana->setGeometry(100,60,150,40);



    avatar = QPixmap(":/ui/images/oldguy.ico");
    unitIcon->setPixmap(avatar.scaled(99,99,Qt::IgnoreAspectRatio));
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
    double scale_factor_icon_w;
    double scale_factor_icon_h;
    double scale_factor_h;
    double scale_factor_name_h;
    double scale_factor_w;
    double scale_factor_mana_y;
    double sf_frame_w;
    double sf_frame_h;


    if(!isParty){
        scale_factor_icon_w = (double)100 / (double)1200;
        scale_factor_icon_h = (double)100 / (double)900;
        scale_factor_h = (double)40 / (double)900;
        scale_factor_name_h = (double)20 / (double)900;
        scale_factor_w = (double)150 / (double)1200;
        scale_factor_mana_y = (double)60 / (double)900;
        sf_frame_w = (double)250 / (double)1200;
        sf_frame_h = (double)100 / (double)900;

        //todo fix icon scaling too
        unitIcon->setPixmap(avatar.scaled(newSize.width()*scale_factor_icon_w,
                                          newSize.height()*scale_factor_icon_h,
                                          Qt::IgnoreAspectRatio));

        name->setGeometry(newSize.width()*scale_factor_icon_w,
                          0,
                          newSize.width()*scale_factor_w,
                          newSize.height()*scale_factor_name_h);

        unitIcon->setGeometry(0,0,
                              newSize.width()*scale_factor_icon_w,
                              newSize.height()*scale_factor_icon_h);
        health->setGeometry(newSize.width()*scale_factor_icon_w,
                            newSize.height()*scale_factor_name_h,
                            newSize.width()*scale_factor_w,
                            newSize.height()*scale_factor_h);
        mana->setGeometry(newSize.width()*scale_factor_icon_w,
                          newSize.height()*scale_factor_mana_y,
                          newSize.width()*scale_factor_w,
                          newSize.height()*scale_factor_h);

        resize(newSize.width()*sf_frame_w,
              newSize.height()*sf_frame_h);
    }
    else{
        scale_factor_icon_w = ((double)100 * partyScale)/ (double)1200;
        scale_factor_icon_h = ((double)100 * partyScale)/ (double)900;
        scale_factor_h = ((double)40 * partyScale)/ (double)900;
        scale_factor_name_h = ((double)20* partyScale) / (double)900;
        scale_factor_w = ((double)150* partyScale) / (double)1200;
        scale_factor_mana_y = ((double)60* partyScale) / (double)900;
        sf_frame_w = ((double)250 * partyScale) / (double)1200;
        sf_frame_h = ((double)100 * partyScale)/ (double)900;

        //todo fix icon scaling too
        unitIcon->setPixmap(avatar.scaled(newSize.width()*scale_factor_icon_w,
                                          newSize.height()*scale_factor_icon_h,
                                          Qt::IgnoreAspectRatio));

        name->setGeometry(newSize.width()*scale_factor_icon_w,
                          0,
                          newSize.width()*scale_factor_w,
                          newSize.height()*scale_factor_name_h);

        unitIcon->setGeometry(0,0,
                              newSize.width()*scale_factor_icon_w,
                              newSize.height()*scale_factor_icon_h);
        health->setGeometry(newSize.width()*scale_factor_icon_w,
                            newSize.height()*scale_factor_name_h,
                            newSize.width()*scale_factor_w,
                            newSize.height()*scale_factor_h);
        mana->setGeometry(newSize.width()*scale_factor_icon_w,
                          newSize.height()*scale_factor_mana_y,
                          newSize.width()*scale_factor_w,
                          newSize.height()*scale_factor_h);

        resize(newSize.width()*sf_frame_w,
              newSize.height()*sf_frame_h);
    }
    return;
}

void UnitFrame::setAvatar(QPixmap newAva){
    avatar = newAva;
}
