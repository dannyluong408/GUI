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

void Chatbox::resizeMe(QSize size){
//    const double scale_factor = (double)50 /(double)1080;


}
