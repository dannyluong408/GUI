#include "chatbox.h"



Chatbox::Chatbox(QWidget *parent)
    : QTextEdit(parent)
{
    setGeometry(0,700,200,200);
    viewport()->setAutoFillBackground(true);

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(255/2,255/2,255/2));
    setPalette(p);
    setTextColor(Qt::cyan);
}

void Chatbox::resizeMe(QSize size){ //fix this too for 1080p
    const double scale_factor_y = (double)700/(double)900;
    const double scale_factor_w = (double)200/(double)1200;
    const double scale_factor_h = (double)200/(double)900;

    move(0,size.height()*scale_factor_y);
    resize(size.width()*scale_factor_w,size.height()*scale_factor_y);
}
