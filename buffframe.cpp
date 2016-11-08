#include "buffframe.h"
#include <QtGlobal>

static bool lessThan(const BuffIcon* e1, const BuffIcon* e2){
    return e1->getBuffDuration() < e2->getBuffDuration();
}

BuffFrame::BuffFrame(QWidget *parent)
    : QFrame(parent)
{
    setObjectName(QStringLiteral("buffFrame"));
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    resize(250,25);
    buffLayout = new QGridLayout(this);
    buffLayout->setSpacing(5);
    buffLayout->setMargin(0);

    test();
    sort();
}

void BuffFrame::resizeMe(QSize newSize) {
    const double scale_factor = (double)25 / (double)1080;
    resize(QSize(newSize.height()*scale_factor , newSize.height()*scale_factor));
    const int minsize = (newSize.height() > newSize.width()) ? newSize.width() : newSize.height();
    //reposition here
    int count = 0;
    for (BuffIcon* i: buffs) {
       i->move(QPoint(scale_factor*minsize*count,100*scale_factor));
       count++;
    }
}

void BuffFrame::sort(){
    qSort(buffs.begin(),buffs.end(),lessThan);

    delete(buffLayout);
    buffLayout = new QGridLayout(this);
    buffLayout->setSpacing(5);
    buffLayout->setMargin(0);

    BuffIcon **temp = buffs.data();
    for(int i = 0; i< buffs.size(); i++){
        buffLayout->addWidget(temp[i],i/10,i%10);
    }
}

void BuffFrame::test(){
    for(int i = buffs.size(); i < 10; i++){
        BuffIcon *buff = new BuffIcon(this);
        switch(i%4){
            case 0:
                buff->setStyleSheet("border: 1px solid black");
                break;
            case 1:
                buff->setStyleSheet("border: 1px solid green");
                break;
            case 2:
                buff->setStyleSheet("border: 1px solid blue");
                break;
            case 3:
                buff->setStyleSheet("border: 1px solid red");
                break;
            default:
                buff->setStyleSheet("border: 1px solid yellow");
                break;
        }
        buff->setPixmap(QPixmap(":/ui/images/oldguy.ico").scaled(24,24,Qt::KeepAspectRatio));
//        buff->setOGPix(buff->pixmap());
        buff->setText(QString::number(i));
        buff->setBuffDuration(qrand() % 1000);
        //qDebug() << i << buff->getBuffDuration();

        buffLayout->addWidget(buff,i/10,i%10);
        buffs.push_back(buff);
    }
}

//void BuffFrame::insertBuff(BuffIcon* buff){
//    buffs.push_back(buff);
//}

//void BuffFrame::removeBuff(BuffIcon* buff){
//
//}


