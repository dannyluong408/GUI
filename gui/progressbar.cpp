#include "GUI/progressbar.h"


ProgressBar::ProgressBar(QWidget *parent)
    : QProgressBar(parent)
{
}

void ProgressBar::resizeMe(QSize newSize){
    const double scale_factor_h = (double)40 / (double)1080;
    const double scale_factor_w = (double)150 / (double)1080;
    resize(newSize.width()*scale_factor_w,newSize.height()*scale_factor_h);
}

