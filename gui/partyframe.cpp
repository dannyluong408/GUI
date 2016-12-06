#include "GUI/partyframe.hpp"

PartyFrame::PartyFrame(QWidget *parent)
    : QFrame(parent)
{
    setStyleSheet("border: none;"
                  "background-color: white;");

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(1);
    mainLayout->setSpacing(1);

    scale = 2.0/3.0;

    for(int i = 0; i< 2; i++){
        player[i] = new UnitFrame(this);
        mainLayout->addWidget(player[i]);
        player[i]->setIsParty(true);
        player[i]->setScale(scale);
        player[i]->resizeMe(QSize(1200.0,900.0));
    }
    resize(262.0*scale,202.0*scale);
}



void PartyFrame::resizeMe(QSize newSize){
    const double scale_factor_w = 262.0*scale / 900.0;
    const double scale_factor_h = 202.0*scale / 900.0;

    this->resize(newSize.height()*scale_factor_w,
                 newSize.height()*scale_factor_h);

    for(int i = 0; i<2; i++){
        player[i]->resizeMe(newSize);
    }
    return;
}
