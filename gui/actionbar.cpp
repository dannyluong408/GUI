#include <QtWidgets>

#include "GUI/actionbar.h"
#include "GUI/gamescreen.hpp"
#include <cassert>

#include "GUI/mainwindow.h"


ActionBar::ActionBar(QWidget *parent)
    : QFrame(parent)
{
    setAcceptDrops(true);
    setObjectName("actionBar");
    resize(50*NUMBUTTONS,50);
    setStyleSheet("#actionBar{"
                  "border: 1px solid black;}");

    actionBarGrid = new QGridLayout(this);
    actionBarGrid->setSpacing(1);
    actionBarGrid->setMargin(1);

    for (int i = 0 ; i < NUMBUTTONS; i++){
        buttonSet[i] = new PushButton(this);
        buttonSet[i]->setSpellbookBool(false);
        connect(buttonSet[i],SIGNAL(spellPickedUp(uint32_t)),this,SIGNAL(spellPickedUp(uint32_t)));
        buttonSet[i]->setSpellId(0);
        buttonSet[i]->setIconSize(QSize(48, 48));
        actionBarGrid->addWidget(buttonSet[i],0,i);
    }
    index = -1;
}

uint32_t ActionBar::getCursorID() {
    return mainwindow->getCursorID();
}

void ActionBar::setIndex(int i){
    assert(i>=0 && i<MAXBARS);
    index = i;
}

int ActionBar::getIndex(){
    return index;
}

void ActionBar::callSlotSpell(int i){
    buttonSet[i]->doThisClicked();
}

void ActionBar::resizeMe(QSize newSize){
    const double minSize = 900.0;
    double scale_factor_y = 48.0/minSize;

    for (int i = 0; i < NUMBUTTONS; i++){
         buttonSet[i]->move(50*i,0);
         buttonSet[i]->resizeMe(newSize);
         buttonSet[i]->setGeometry(newSize.height()*scale_factor_y*i,
                                   0,
                                   newSize.height()*scale_factor_y,
                                   newSize.height()*scale_factor_y);
    }

    double scale = 50.0/900.0;

    this->resize(newSize.height()*scale*NUMBUTTONS,
            newSize.height()*scale);

    scale_factor_y = 800.0 / 900.0;
    const double scale_height = 50.0 / 900.0;

    this->move(newSize.width() /2 -  this->size().width()/2,
               newSize.height()*scale_factor_y + newSize.height()*scale_height*index);
    return;
}

//1200 = 350, 600 - 250  , 656 frame actual 454 wtf?
//900.0 =     , 450 - ?

void ActionBar::setButtonSpell(uint32_t spellid, uint32_t buttonNum){
    if(buttonNum < 1 || buttonNum > 10){
        qDebug() << "Invalid Input";
        return;
    }
    buttonSet[buttonNum-1]->setSpellId(spellid);
}

uint32_t ActionBar::getButtonSpell(uint32_t buttonNum){
    if(buttonNum < 1 || buttonNum > 10){
        qDebug() << "Invalid Input";
        return 0;
    }
    return buttonSet[buttonNum-1]->getSpellId();
}

void ActionBar::setMainBarHotkey(){
    for (int i = 0 ; i < NUMBUTTONS; i++){
        if (i == 9) {
           buttonSet[i]->setShortcut(Qt::Key_0);
        }
        else if (i < 9){
           buttonSet[i]->setShortcut(Qt::Key_0 + (i+1));
        }
    }
}

void ActionBar::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata2")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            printf("AB Inside1\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("AB Outside1\n");
            fflush(stdout);
        }
    } else {
        event->ignore();
    }
}

void ActionBar::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata2")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void ActionBar::dropEvent(QDropEvent *event)
{
    qDebug() << "Triggered";

    if (event->mimeData()->hasFormat("application/x-dnditemdata2")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata2");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

//        QLabel *newIcon = new QLabel(this);
//        newIcon->setPixmap(pixmap);
//        newIcon->move(event->pos() - offset);
//        newIcon->show();
//        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            printf("AB Inside DnD\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("AB Outside DnD\n");
            fflush(stdout);
        }
    }

    else if (event->mimeData()->hasFormat("application/x-dnditemdata2")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata2 ");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            printf("AB Inside DnD\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("AB Outside DnD\n");
            fflush(stdout);
        }
    }
    else {
        event->ignore();
    }
}

void ActionBar::mousePressEvent(QMouseEvent *event)
{
    printf("AB Printed This Trying to Drag the Action Bar :TODO!!!\n");
    fflush(stdout);

    QPixmap pixmap;
    QPushButton *child= (QPushButton*)childAt(event->pos());
    PushButton *child2 = (PushButton*)child;

    if(child2)
    qDebug() << child2->metaObject()->className();

    if( child2 && ((QString)child2->metaObject()->className() == "QPushButton")){
        QIcon icon;
        pixmap = child2->icon().pixmap(65,65);
        qDebug() << "AB Its valid!";
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pixmap << QPoint(event->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata2", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos());

        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();

        //child2->setPixmap(tempPixmap);
        QIcon buttonIcon(tempPixmap);
        child2->setIcon(buttonIcon);
        child2->setIconSize(pixmap.rect().size());

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
            //child2->close();
            child2->show();
            qDebug() << "AB Inside4";
            fflush(stdout);
        } else {
             child2->show();
             qDebug() << "AB Outside4\n";
             fflush(stdout);
        }
    }
    else{
        mainwindow->setCursorID(0);
    }
    return;
}

