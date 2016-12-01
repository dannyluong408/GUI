#include "honorframe.hpp"


HonorFrame::HonorFrame(QWidget *parent)
    : QFrame(parent)
{
    setObjectName("honorFrame");
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    setGeometry(500,200,300,400);
    setStyleSheet("border: 1px solid black;"
                  "background-color: white;");


    honorName = new QLabel(this);
    honorName->setText("Honor");
    honorName->setStyleSheet("border: 1px solid black;");
    honorName->setGeometry(40,0,245,15);
    honorName->setAlignment(Qt::AlignCenter);

    x = new QPushButton(this);
    x->setText("X");
    x->setGeometry(285,0,15,15);
    connect(x,SIGNAL(clicked(bool)),this,SLOT(hide()));

    honorLogo = new QLabel(this);
    honorLogoPix = QPixmap(":/ui/images/oldguy.ico");
    honorLogo->setPixmap(honorLogoPix.scaled(40,40,Qt::KeepAspectRatio));
    honorLogo->setGeometry(0,0,40,40);


    setVisible(false);
}

void HonorFrame::resizeMe(QSize size){
    double scale_x = 300.0/900.0;
    double scale_y = 400.0/900.0;

    double new_h = size.height();

    //parent frame
    resize(new_h*scale_x,
           new_h*scale_y);


    //honor frame name
    scale_x = 40.0/900.0;
    double scale_w = 245.0/900.0;
    double scale_h = 15.0/900.0;


    honorName->setGeometry(new_h*scale_x,
                           0,
                           new_h*scale_w,
                           new_h*scale_h);

    //x
    scale_x = 285.0/900.0;
    scale_w = 15.0/900.0;
    scale_h = 15.0/900.0;

    x->setGeometry(new_h*scale_x,
                   0,
                   new_h*scale_w,
                   new_h*scale_h);

    //honorLogo
    scale_w = 40.0/900.0;
    scale_h = 40.0/900.0;

    honorLogo->setGeometry(0,
                           0,
                           new_h*scale_w,
                           new_h*scale_h);
    honorLogo->setPixmap(honorLogoPix.scaled(new_h*scale_w,
                                             new_h*scale_h,
                                             Qt::KeepAspectRatio));


    return;

}

void HonorFrame::hide(){
    setVisible(false);
}
