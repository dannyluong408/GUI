#include "GUI/targetbuffframe.hpp"
#include <QtGlobal>
#include <cassert>
#include <GUI/mainwindow.h>

#define BUFF true
#define DEBUFF false

static QString getBuffStyle(uint32_t buffid){
    //return the stylesheet border for the buff here;
    buffid = buffid;
    return QString("test");
}

//restore this later
//static bool lessThan(const BuffIcon* e1, const BuffIcon* e2){
//    return e1->getBuffDuration() < e2->getBuffDuration();
//}

static bool lessThan(BuffIcon* e1, BuffIcon* e2){
    return e1->getBuffID() < e2->getBuffID();
}

TargetBuffFrame::TargetBuffFrame(QWidget *parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    resize(260,50);

    buffFrame = new QFrame(this);
    buffFrame->setGeometry(0,0,260,25);
    buffLayout = new QGridLayout(buffFrame);
    buffLayout->setSpacing(1);
    buffLayout->setMargin(1);
    test(BUFF);

    debuffFrame = new QFrame(this);
    debuffFrame->setGeometry(0,25,260,25);
    debuffLayout = new QGridLayout(debuffFrame);
    debuffLayout->setSpacing(1);
    debuffLayout->setMargin(1);
    setStyleSheet("border: none");
    test(DEBUFF);
}

static QString temp = ".BuffIcon{"
               "border: 1px solid yellow;"
               "color: black;}";

void TargetBuffFrame::insertBuff(uint32_t buffid){
    assert(buffid < 1000); // change this later to whatever the highest possible buffid is
    if(buffid % 2 == 0){
        if (buffs.size() >= 20){
            qDebug() << "How to handle when over 20 buffs?";
            return;
        }
        BuffIcon *buff = new BuffIcon(this);
        buff->setBuffID(buffid);
        buff->setText(QString::number(buffid));
        buff->setStyleSheet(temp);
        buff->setBuffDuration(0); // map function to default duration?
        buffs.push_back(buff);
        sort(BUFF);
    }
    else{
        if (debuffs.size() >= 20){
            qDebug() << "How to handle when over 20 debuffs?";
            return;
        }
        BuffIcon *debuff = new BuffIcon(this);
        debuff->setBuffID(buffid);
        debuff->setText(QString::number(buffid));
        debuff->setStyleSheet(temp);
        debuff->setBuffDuration(0); // map function to default duration?
        debuffs.push_back(debuff);
        sort(DEBUFF);
    }
}

void TargetBuffFrame::removeBuff(uint32_t buffid){ // find buff and pop, else return error
    assert(buffid < 1000); // change this later to whatever the highest possible buffid is

    BuffIcon **buffIter = nullptr, *removeMarker = nullptr;

    if(buffid % 2 == 0){
        buffIter = buffs.data();

        for(int i = 0; i< buffs.size(); i++){
            if(buffIter[i]->getBuffID() == buffid){
                removeMarker = buffIter[i];
                buffs.remove(i);
                buffLayout->removeWidget(buffIter[i]);
                sort(BUFF);
                break;
            }
        }
    }

    else{
        qDebug() << "Removing Debuff:" << buffid;
        buffIter = debuffs.data();

        for(int i = 0; i< debuffs.size(); i++){
            if(buffIter[i]->getBuffID() == buffid){
                removeMarker = buffIter[i];
                debuffs.remove(i);
                debuffLayout->removeWidget(buffIter[i]);
                sort(DEBUFF);
                break;
            }
        }
    }
    delete removeMarker;
    buffIter = nullptr;
    delete buffIter;
    qDebug() << "Error buffid not found!";
    return;
}

void TargetBuffFrame::shiftMe(bool shift){
    if (shift){
    this->move(this->pos().x(),this->pos().y()+42);
    }
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

    sort(BUFF);
    sort(DEBUFF);
    return;
}

void TargetBuffFrame::sort(bool buff){
    int i;
    const double scale = 25.0 / 900.0;
    const double scale2 = 26.0 / 900.0;
    this->resize(this->width(),
                ((buffs.size()/10+1)+(debuffs.size()/10+1))*
                 mainwindow->height()*scale);
    if(buff){
        qSort(buffs.begin(),buffs.end(),lessThan);
        if (buffs.size() > 10){
            buffFrame->resize(this->width(),mainwindow->height()*scale*2);
        }
        else{
            buffFrame->resize(this->width(),mainwindow->height()*scale);

        }
        debuffFrame->move(0,buffFrame->height());

        delete(buffLayout);
        buffLayout = new QGridLayout(buffFrame);
        buffLayout->setSpacing(1);
        buffLayout->setMargin(1);
        buffLayout->setColumnStretch(0,1);
        buffLayout->setRowMinimumHeight(0,mainwindow->height()*scale);
        if(buffs.size() > 10){
            buffLayout->setColumnStretch(1,1);
            buffLayout->setRowMinimumHeight(1,mainwindow->height()*scale);
        }
        for(i = 0; i<10; i++){
            buffLayout->setColumnStretch(i,1);
            buffLayout->setColumnMinimumWidth(i,mainwindow->height()*scale);
        }

        BuffIcon **temp = buffs.data();
        for(i = 0; i< buffs.size(); i++){
            buffLayout->addWidget(temp[i],i/10,i%10);
        }

        if (buffs.size() < 10){
            for(i = buffs.size(); i< 10; i++){
                QSpacerItem *spacer;
                spacer = new QSpacerItem(mainwindow->height()*scale,
                                         mainwindow->height()*scale,
                                         QSizePolicy::Ignored,
                                         QSizePolicy::Ignored);
                buffLayout->addItem(spacer,i/10,i%10);
            }
        }
        else if(buffs.size() != 10 && buffs.size() < 20){
            for(i = buffs.size(); i<20; i++){
                QSpacerItem *spacer;
                spacer = new QSpacerItem(mainwindow->height()*scale,
                                         mainwindow->height()*scale,
                                         QSizePolicy::Ignored,
                                         QSizePolicy::Ignored);
                buffLayout->addItem(spacer,i/10,i%10);
            }
        }
    }
    else{
        qSort(debuffs.begin(),debuffs.end(),lessThan);
        if (debuffs.size() > 10){
            debuffFrame->resize(this->width(),mainwindow->height()*scale*2);
        }
        else{
            debuffFrame->resize(this->width(),mainwindow->height()*scale);

        }
        debuffFrame->move(0,buffFrame->height());

        delete(debuffLayout);
        debuffLayout = new QGridLayout(debuffFrame);
        debuffLayout->setSpacing(1);
        debuffLayout->setMargin(1);
        debuffLayout->setColumnStretch(0,1);
        debuffLayout->setRowMinimumHeight(0,mainwindow->height()*scale);
        if(debuffs.size() > 10){
            debuffLayout->setColumnStretch(1,1);
            debuffLayout->setRowMinimumHeight(1,mainwindow->height()*scale);
        }
        for(i = 0; i<10; i++){
            debuffLayout->setColumnStretch(i,1);
            debuffLayout->setColumnMinimumWidth(i,mainwindow->height()*scale);
        }

        BuffIcon **temp = debuffs.data();
        for(i = 0; i< debuffs.size(); i++){
            debuffLayout->addWidget(temp[i],i/10,i%10);
        }

        if (debuffs.size() < 10){
            for(i = debuffs.size(); i< 10; i++){
                QSpacerItem *spacer;
                spacer = new QSpacerItem(mainwindow->height()*scale,
                                         mainwindow->height()*scale,
                                         QSizePolicy::Ignored,
                                         QSizePolicy::Ignored);
                debuffLayout->addItem(spacer,i/10,i%10);
            }
        }
        else if(debuffs.size() != 10 && debuffs.size() < 20){
            for(i = debuffs.size(); i<20; i++){
                QSpacerItem *spacer;
                spacer = new QSpacerItem(mainwindow->height()*scale,
                                         mainwindow->height()*scale,
                                         QSizePolicy::Ignored,
                                         QSizePolicy::Ignored);
                debuffLayout->addItem(spacer,i/10,i%10);
            }
        }
    }
}

void TargetBuffFrame::test(bool buff){
    int i;
    if (buff){
        i = buffs.size();
    }
    else{
        i = debuffs.size();
    }
    for(i = 0; i < 10; i++){
        BuffIcon *newBuff = new BuffIcon(this);
        newBuff->resizeMe(QSize(1200,900));
        newBuff->setBuffID(i);
        switch(i%4){
            case 0:{
                newBuff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid black;"
                                    "color: black;}");
                                    //"color: white;}");
                break;
            }
            case 1:{
                newBuff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid green;"
                                    "color: black;}");
                                    //"color: white;}");
                break;
            }
            case 2:{
                newBuff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid blue;"
                                    "color: black;}");
                                    //"color: white;}");
                break;
            }
            case 3:{
                newBuff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid red;"
                                    "color: black;}");
                                    //"color: white;}");
                break;}

            default:{
                newBuff->setStyleSheet(".BuffIcon{"
                                    "border: 1px solid yellow;"
                                    "color: black;}");
                                    //"color: white;}");
                break;
            }
        }

        newBuff->setText(QString::number(i));
        newBuff->setBuffDuration(qrand() % 1000);

        if (buff){
            buffLayout->addWidget(newBuff,i/10,i%10);
            buffs.push_back(newBuff);
        }
        else{
            debuffLayout->addWidget(newBuff,i/10,i%10);
            debuffs.push_back(newBuff);
        }
    }
}
