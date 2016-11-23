#include "playerBuffFrame.hpp"
#include <QtGlobal>

static bool lessThan(const BuffIcon* e1, const BuffIcon* e2){
    return e1->getBuffDuration() < e2->getBuffDuration();
}

PlayerBuffFrame::PlayerBuffFrame(QWidget *parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    resize(420,42);
    buffLayout = new QGridLayout(this);
    buffLayout->setSpacing(1);
    buffLayout->setMargin(0);
    buffLayout->setOriginCorner(Qt::TopRightCorner);
    setStyleSheet("border: none");
    isDebuff = false;
    test();
    sort();
    resizeMe(QSize(1200,900));
}

void PlayerBuffFrame::shiftMe(bool shift){
    if (shift && this->isDebuff){
        this->move(this->pos().x(),this->pos().y()+42);
    }
    else if (!shift && this->isDebuff){
        this->move(this->pos().x(),this->pos().y()-42);
    }
}

void PlayerBuffFrame::setAsDebuff(bool state){
    isDebuff = state;
}

void PlayerBuffFrame::resizeMe(QSize newSize) {
    const double minSize = 900.0;
    const double iconSize = 42.0 / minSize;
    const double scale_factor = 15.0 / minSize;
    const double padding = 15.0 / 1200.0;
    const double spacing = 44.0 / minSize;
    const double offset = 43.0 / minSize;

    if (!isDebuff){
        setGeometry(newSize.width()-((newSize.height()*iconSize*10+10+newSize.width()*padding)),
                    newSize.height()*scale_factor,
                    newSize.height()*iconSize*10+10,
                    newSize.height()*spacing);
    }
    else{
        setGeometry(newSize.width()-((newSize.height()*iconSize*10+10+newSize.width()*padding)),
                    newSize.height()*scale_factor+newSize.height()*offset,
                    newSize.height()*iconSize*10+10,
                    newSize.height()*spacing);
    }

    BuffIcon **temp = buffs.data();
    for(int i = 0; i< buffs.size(); i++){
        temp[i]->resizeMe(newSize);
    }
    temp = nullptr;
    free(temp);
    return;
}

void PlayerBuffFrame::sort(){
    qSort(buffs.begin(),buffs.end(),lessThan);

    delete(buffLayout);
    buffLayout = new QGridLayout(this);
    buffLayout->setSpacing(1);
    buffLayout->setMargin(1);

    BuffIcon **temp = buffs.data();
    for(int i = 0; i< buffs.size(); i++){
        buffLayout->addWidget(temp[i],i/10,i%10);
    }

}

void PlayerBuffFrame::test(){
    for(int i = buffs.size(); i < 10; i++){
        BuffIcon *buff = new BuffIcon(this);
        buff->setIsPlayer(true);
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
//        buff->setOGPixmap(QPixmap(":/ui/images/oldguy.ico").scaled(42,42,Qt::KeepAspectRatio));
//        buff->setOGPix(buff->pixmap());
        buff->setText(QString::number(i));
        buff->setBuffDuration(qrand() % 1000);
        //qDebug() << i << buff->getBuffDuration();

        buffLayout->addWidget(buff,i/10,i%10);
        buffs.push_back(buff);
    }
}

//void PlayerBuffFrame::insertBuff(BuffIcon* buff){
//    buffs.push_back(buff);
//}

//void PlayerBuffFrame::removeBuff(BuffIcon* buff){
//
//}


