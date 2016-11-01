#include <QtWidgets>

#include "actionbar.h"

ActionBar::ActionBar(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    setFixedSize(65*NUMBUTTONS,65);

    buttonGroup = new QButtonGroup;

    for (int i = 0 ; i < NUMBUTTONS; i++){
        buttonSet[i] = new PushButton(this);
        buttonSet[i]->setFixedSize(55,55);
        buttonSet[i]->move(65*i,0);

        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(buttonSet[i]->sizePolicy().hasHeightForWidth());
        buttonSet[i]->setSizePolicy(sizePolicy3);
        QIcon icon;
        icon.addFile(QStringLiteral("../NADL/oldguy.ico"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSet[i]->setIcon(icon);
        buttonSet[i]->setIconSize(QSize(50, 50));

        buttonGroup->addButton(buttonSet[i]);
        buttonGroup->setId(buttonSet[i], i+1);
    }

    qDebug() << buttonGroup->buttons();
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
    printf("AB Printed This\n");
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
