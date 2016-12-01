#include <QtWidgets>

#include "dragpushbutton.h"

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
    QIcon newIcon;
    switch(spell_id){
        case 1:
            newIcon.addFile(QStringLiteral(":/ui/images/boat.png"), QSize(), QIcon::Normal, QIcon::Off);
            break;
        case 2:
            newIcon.addFile(QStringLiteral(":/ui/images/car.png"), QSize(), QIcon::Normal, QIcon::Off);
            break;
        case 3:
            newIcon.addFile(QStringLiteral(":/ui/images/house.png"), QSize(), QIcon::Normal, QIcon::Off);
            break;
        case 0:
            newIcon.addFile(QStringLiteral(":/ui/images/oldguy.ico"), QSize(), QIcon::Normal, QIcon::Off);
            break;
    }
    setIcon(newIcon);
    origIcon = newIcon.pixmap(QSize(48,48));
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
            printf("DPB Inside1\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("DPB Outside1\n");
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

//        qDebug() << "DPB This Pos" << this->pos();
//        qDebug() << "DPB Event Pos" << event->pos();


        QByteArray itemData = event->mimeData()->data("spellData");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        uint32_t newSpellId;
        dataStream >> newSpellId;

//        qDebug() << "Lol" << this->metaObject()->className();
//        qDebug() << "Global Pos" << mapToGlobal(this->pos());
        qDebug() << "Old SpellID:" << this->getSpellId();
        qDebug() << "New SpellID:" << newSpellId;


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
        }
    } else {
        event->ignore();
    }
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "QAPPDD1:" << QApplication::startDragDistance();
    if (event->button() == Qt::LeftButton){
        dragStartPosition = event->pos();
        //qDebug() << "DPB PressEvent" << dragStartPosition;
        this->click();
    }
    else{
        qDebug() << "???";
    }
}

void PushButton::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "DPB Printed This\n";

    //qDebug() << "EventPos:" << event->pos();
    //qDebug() << "DragStartPos:" << dragStartPosition;
    //qDebug() << "QAPPDD2:" << QApplication::startDragDistance();

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
        //Transfers info to the drag
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << child->spell_id;
        QMimeData *mimeData = new QMimeData;
        mimeData->setData("spellData", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        QIcon dragIcon = child->icon();
        drag->setPixmap(dragIcon.pixmap(QSize(50,50)));
        drag->setHotSpot(event->pos());

//        //This stuff to show icon while dragging
//        QPixmap tempPixmap = pixmap;
//        QPainter painter;
//        painter.begin(&tempPixmap);
//        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
//        painter.end();
//        QIcon buttonIcon(tempPixmap);
//        child->setIcon(buttonIcon);
//        child->setIconSize(pixmap.rect().size());


        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
            child->show();
            printf("DPB Inside4\n");
            fflush(stdout);
        } else {
             if(!spellbookIcon){
                 child->setSpellId(0);
             }
             printf("DPB Outside4\n");
             fflush(stdout);
        }
    }
    return;
}
