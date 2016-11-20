#include <QtWidgets>

#include "actionbar.h"

ActionBar::ActionBar(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    resize(50*NUMBUTTONS,50);
    setStyleSheet("border-color:black;");

    buttonGroup = new QButtonGroup;

    for (int i = 0 ; i < NUMBUTTONS; i++){
        buttonSet[i] = new PushButton(this);
        buttonSet[i]->move(50*i,0);
        QIcon icon;
        icon.addFile(QStringLiteral("../NADL/oldguy.ico"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSet[i]->setIcon(icon);
        buttonSet[i]->setIconSize(QSize(48, 48));

        buttonGroup->addButton(buttonSet[i]);
        buttonGroup->setId(buttonSet[i], i+1);
    }
}



void ActionBar::callSlotSpell(int i){
    buttonSet[i]->doThisClicked();
}

void ActionBar::resizeMe(QSize newSize){
    double scale_factor_x  = (50.0*NUMBUTTONS)/1200.0;
    const double scale_factor_y = 50.0/900.0;

    resize(newSize.width()*scale_factor_x,
           newSize.height()*scale_factor_y);


    scale_factor_x  = 50.0/1200.0;
    for (int i = 0; i < NUMBUTTONS; i++){
         buttonSet[i]->resizeMe(newSize);
         buttonSet[i]->setGeometry((newSize.width()*scale_factor_x*(double)i),
                                   0,
                                   newSize.width()*scale_factor_x,
                                   newSize.height()*scale_factor_y);
    }
    return;
}

void ActionBar::setButtonSpell(uint32_t spellid, uint32_t buttonNum){
    buttonSet[buttonNum-1]->setSpellId(spellid);
}

uint32_t ActionBar::getButtonSpell(uint32_t buttonNum){
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
    return;
}

