#include <QtWidgets>

#include "GUI/dragpushbutton.h"
#include "GUI/actionbar.h"
#include "GUI/spellbook.h"
#include "GUI/mainwindow.h"

PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
    dragStartPosition.setX(0);
    dragStartPosition.setY(0);
    resize(QSize(50,50));
    setAcceptDrops(true);
    setObjectName(QStringLiteral("dragPushButton"));
    QIcon icon;
    icon.addFile(QStringLiteral(":/ui/images/oldguy.ico"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon(icon);
    setIconSize(QSize(48, 48));
    setAttribute(Qt::WA_DeleteOnClose);
    connect(this,SIGNAL(clicked(bool)),this,SLOT(doThisClicked()));
    connect(this,SIGNAL(valueChanged(bool)),this,SLOT(updateIcon(bool))); 
    origIcon = icon.pixmap(48,48);
    spell_id = 0;
    spellbookIcon = true;
    setStyleSheet("border: 1px solid black"); //temp change it dynamically later
    show();
}

void PushButton::setSpellbookBool(bool value){
    spellbookIcon = value;
}

void PushButton::resizeMe(QSize newSize){
    const double minSize = 900.0;
    const double square_icon_frame = 50.0 / minSize;
    this->resize(newSize.height()*square_icon_frame,
                 newSize.height()*square_icon_frame);
    const double square_icon = 48.0 / minSize;
    //qDebug() << "Resizing Spell Buttons " << newSize;
    this->setIconSize(QSize(newSize.height()*square_icon,
                      newSize.height()*square_icon));
    setIcon(QIcon(origIcon.scaled(newSize.height()*square_icon,
                                  newSize.height()*square_icon,
                                  Qt::KeepAspectRatio)));
}




void PushButton::doThisClicked(){
    qDebug() << "Do stuff here when pressed!";
}

void PushButton::setSpellId(uint32_t spellid){
    spell_id = spellid;
    //find the corresponding icon for the spellid and add to origIcon;
    emit valueChanged(true);
}

void PushButton::updateIcon(bool changed){
    if (changed != true){
        return;
    }
    //ghetto map here for now to test
    //updat later with real id to icon map
    QPixmap pixmap;
    switch(spell_id){
        case 1:
            pixmap = QPixmap(":/ui/images/boat.png");
            break;
        case 2:
            pixmap = QPixmap(":/ui/images/car.png");
            break;
        case 3:
            pixmap = QPixmap(":/ui/images/house.png");
            break;
        case 0:
            pixmap = QPixmap(":/ui/images/oldguy.ico");
            break;
    }
    origIcon = pixmap;
    QIcon newIcon(pixmap.scaled(this->width(),this->height(),Qt::KeepAspectRatio));
    setIcon(newIcon);
}


uint32_t PushButton::getSpellId(){
    return spell_id;
}


void PushButton::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("spellData")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            fflush(stdout);
        }
    } else {
        event->ignore();
    }
}

void PushButton::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("spellData")) {
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

void PushButton::dropEvent(QDropEvent *event)
{

    if (event->mimeData()->hasFormat("spellData")) {

        bool pickup = false;
        const uint32_t oldSpellId = this->getSpellId();

        QByteArray itemData = event->mimeData()->data("spellData");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        uint32_t newSpellId;
        dataStream >> newSpellId;

        qDebug() << "Old SpellID:" << this->getSpellId();
        qDebug() << "New SpellID:" << newSpellId;


        if(this->getSpellId() != 0){
            pickup = true;
        }
        qDebug() << "New Spell!";
        this->setSpellId(newSpellId);


        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            printf("DPB Inside DnD\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("DPB Outside DnD\n");
            fflush(stdout);
            if(pickup){
                qDebug() << "Emitted!";
                emit spellPickedUp(oldSpellId);
            }
        }
    } else {
        event->ignore();
    }
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
    uint32_t mouseID;
    if(!spellbookIcon){
        ActionBar *info = (ActionBar*)parent();
        mouseID = info->getCursorID();
        qDebug() << "Action ID" << mouseID;
    }
    else{
        qDebug() << "Clear";
        emit spellPickedUp(0);
        return;
    }


    if (event->button() == Qt::LeftButton){
        dragStartPosition = event->pos();
        if(mouseID != 0 && !spellbookIcon){
            qDebug() << "Not zero";
            this->setSpellId(mouseID);
            emit spellPickedUp(0);
        }
        this->click();
    }
    else{
        qDebug() << "???";
    }
}

void PushButton::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()){
           //qDebug() <<  (event->pos() - dragStartPosition).manhattanLength()<<" vs " <<  QApplication::startDragDistance();
           return;
    }

    QPixmap pixmap;
    PushButton *child = this;
    //qDebug() << child->metaObject()->className();

    if( child && ((QString)child->metaObject()->className() == "PushButton")){
        //qDebug() << "DPB Its valid!";

        if (spell_id == 0){
            return;
        }

        mainwindow->cursorID = child->spell_id;

        //Transfers info to the drag
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << child->spell_id;
        QMimeData *mimeData = new QMimeData;
        mimeData->setData("spellData", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        QIcon dragIcon = child->icon();
        drag->setDragCursor(dragIcon.pixmap(QSize(50,50)),Qt::MoveAction);
        drag->setHotSpot(event->pos());

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
            child->show();
            qDebug() << "DPB Inside4\n";
            fflush(stdout);
        } else {
             if(!spellbookIcon){
                 child->setSpellId(0);
             }
             qDebug() << "DPB Outside4\n";
             fflush(stdout);
        }
    }
    return;
}
