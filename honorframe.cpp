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
    double scale_x = 300.0/1200.0;
    double scale_y = 400.0/1080.0;

    double new_w = size.width();
    double new_h = size.height();

    //parent frame
    resize(new_w*scale_x,
           new_h*scale_y);


    //honor frame name
    scale_x = 40.0/1200.0;
    double scale_w = 245.0/1200.0;
    double scale_h = 15.0/1080.0;


    honorName->setGeometry(new_w*scale_x,
                           0,
                           new_w*scale_w,
                           new_h*scale_h);

    //x
    scale_x = 285.0/1200.0;
    scale_w = 15.0/1200.0;
    scale_h = 15.0/1080.0;

    x->setGeometry(new_w*scale_x,
                   0,
                   new_w*scale_w,
                   new_h*scale_h);

    //honorLogo
    scale_w = 40.0/1200.0;
    scale_h = 40.0/1080.0;

    honorLogo->setGeometry(0,
                           0,
                           new_w*scale_w,
                           new_h*scale_h);
    honorLogo->setPixmap(honorLogoPix.scaled(new_w*scale_w,
                                             new_h*scale_h,
                                             Qt::KeepAspectRatio));

//    //info
//    scale_x = 40.0/1200.0;
//    scale_y= 15.0/1080.0;
//    scale_w = 75.0/1200.0;
//    scale_h = 15.0/1080.0;

//    info->setGeometry(new_w*scale_x,
//                      new_h*scale_y,
//                      new_w*scale_w,
//                      new_h*scale_h);

//    //settings
//    scale_x = 115.0/1200.0;
//    scale_y = 15.0/1080.0;
//    scale_w = 75.0/1200.0;
//    scale_h = 15.0/1080.0;

//    settings->setGeometry(new_w*scale_x,
//                          new_h*scale_y,
//                          new_w*scale_w,
//                          new_h*scale_h);
//    //add
//    scale_x = 190.0/1200.0;
//    scale_y = 15.0/1080.0;
//    scale_w = 75.0/1200.0;
//    scale_h = 15.0/1080.0;

//    add->setGeometry(new_w*scale_x,
//                     new_h*scale_y,
//                     new_w*scale_w,
//                     new_h*scale_h);

//    //tableview
//    scale_x = 10.0/1200.0;
//    scale_y = 45.0/1080.0;
//    scale_w = 280.0/1200.0;
//    scale_h = 230.0/1080.0;

//    view->setGeometry(new_w*scale_x,
//                      new_h*scale_y,
//                      new_w*scale_w,
//                      new_h*scale_h);

//    //online
//    scale_x = 10.0/1200.0;
//    scale_y = 280.0/1080.0;
//    scale_w = 100.0/1200.0;
//    scale_h = 15.0/1080.0;

//    online->setGeometry(new_w*scale_x,
//                        new_h*scale_y,
//                        new_w*scale_w,
//                        new_h*scale_h);

//    //offline
//    scale_x = 150.0/1200.0;
//    scale_y = 280.0/1080.0;
//    scale_w = 140.0/1200.0;
//    scale_h = 15.0/1080.0;

//    showOffline->setGeometry(new_w*scale_x,
//                             new_h*scale_y,
//                             new_w*scale_w,
//                             new_h*scale_h);

//    //gmotd
//    scale_x = 10.0/1200.0;
//    scale_y = 300.0/1080.0;
//    scale_w = 280.0/1200.0;
//    scale_h = 90.0/1080.0;

//    gmotd->setGeometry(new_w*scale_x,
//                       new_h*scale_y,
//                       new_w*scale_w,
//                       new_h*scale_h);
    return;

}

void HonorFrame::hide(){
    setVisible(false);
}
