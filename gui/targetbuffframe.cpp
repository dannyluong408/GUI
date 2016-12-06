#include "GUI/targetbuffframe.hpp"
#include <QtGlobal>

static bool lessThan(const BuffIcon* e1, const BuffIcon* e2){
    return e1->getBuffDuration() < e2->getBuffDuration();
}

TargetBuffFrame::TargetBuffFrame(QWidget *parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    resize(260.0,25.0);
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
    const double minSize = 900.0;
    const double spacing = 26.0 / minSize;

    resize(newSize.height()*spacing*10,
           newSize.height()*spacing);

    BuffIcon **temp = buffs.data();
    for(int i = 0; i< buffs.size(); i++){
        temp[i]->resizeMe(newSize);
    }
    temp = nullptr;
    free(temp);

    return;
}

void TargetBuffFrame::sort(){
    qSort(buffs.begin(),buffs.end(),lessThan);

    delete(buffLayout);
    buffLayout = new QGridLayout(this);
    buffLayout->setSpacing(1);
    buffLayout->setMargin(1);

    BuffIcon **temp = buffs.data();
    for(int i = 0; i< buffs.size(); i++){
        buffLayout->addWidget(temp[i],i/10,i%10);
    }
    temp = nullptr;
    free(temp);
}

void TargetBuffFrame::test(){
    for(int i = buffs.size(); i < 10; i++){
        BuffIcon *buff = new BuffIcon(this);
        buff->resizeMe(QSize(1200,900));
        switch(i%4){
            case 0:
                buff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid black;"
                                    "color: white;}");
                break;
            case 1:
                buff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid green;"
                                    "color: white;}");
                break;
            case 2:
                buff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid blue;"
                                    "color: white;}");
                break;
            case 3:
                buff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid red;"
                                    "color: white;}");
                break;
            default:
                buff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid yellow;"
                                    "color: white;}");
                break;
        }
//        buff->setPixmap(QPixmap(":/ui/images/oldguy.ico").scaled(24,24,Qt::KeepAspectRatio));
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


