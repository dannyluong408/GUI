#include "targetbuffframe.hpp"
#include <QtGlobal>

static bool lessThan(const BuffIcon* e1, const BuffIcon* e2){
    return e1->getBuffDuration() < e2->getBuffDuration();
}

TargetBuffFrame::TargetBuffFrame(QWidget *parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    resize(250,25);
    buffLayout = new QGridLayout(this);
    buffLayout->setSpacing(1);
    buffLayout->setMargin(1);
    setStyleSheet("border: none");
    isDebuff = false;
    test();
    sort();
}

void TargetBuffFrame::shiftMe(bool shift){
    if (shift && this->isDebuff){
        this->move(this->pos().x(),this->pos().y()+42);
    }
    else if (!shift && this->isDebuff){
        this->move(this->pos().x(),this->pos().y()-42);
    }
}

void TargetBuffFrame::setAsDebuff(bool state){
    isDebuff = state;
}

void TargetBuffFrame::resizeMe(QSize newSize) {
    const double scale_factor_w = (double)250 / (double)1200;
    const double scale_factor_h = (double)25 / (double)900;
    resize(QSize(newSize.width()*scale_factor_w , newSize.height()*scale_factor_h));

}

void TargetBuffFrame::sort(){
    qSort(buffs.begin(),buffs.end(),lessThan);

    delete(buffLayout);
    buffLayout = new QGridLayout(this);
    buffLayout->setSpacing(3);
    buffLayout->setMargin(0);

    BuffIcon **temp = buffs.data();
    for(int i = 0; i< buffs.size(); i++){
        buffLayout->addWidget(temp[i],i/10,i%10);
    }
}

void TargetBuffFrame::test(){
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


