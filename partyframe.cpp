#include "partyframe.hpp"

PartyFrame::PartyFrame(QWidget *parent)
    : QFrame(parent)
{
    setStyleSheet("border: none;"
                  "background-color: white;");

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(1);
    mainLayout->setSpacing(5);

    scale = 2.0/3.0;

    for(int i = 0; i< 2; i++){
        player[i] = new UnitFrame(this);
        mainLayout->addWidget(player[i]);
        player[i]->setIsParty(true);
        player[i]->setScale(scale);
        player[i]->resizeMe(QSize(1200,900));
    }
    resize(251.0*scale,210.0*scale);
}



void PartyFrame::resizeMe(QSize newSize){
    const double scale_factor_w = (double)251*scale / (double) 1200;
    const double scale_factor_h = (double)210*scale / (double) 900;

    this->resize(newSize.width()*scale_factor_w,newSize.height()*scale_factor_h);

    for(int i = 0; i<2; i++){
        player[i]->resizeMe(newSize);
    }
}
