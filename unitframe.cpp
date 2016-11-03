#include "unitframe.h"


UnitFrame::UnitFrame(QWidget *parent)
    : QFrame(parent)
{

}

void UnitFrame::resizeMe(QSize newSize){
    const double scale_factor = (double)32 / (double)1080;
    resize(QSize(newSize.height()*scale_factor , newSize.height()*scale_factor));

}

