#include <QtWidgets>

#include "dragpushbutton.h"

PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
    setFixedSize(50,50);
    setAcceptDrops(true);
    setObjectName(QStringLiteral("dragPushButton"));
    QIcon icon;
    icon.addFile(QStringLiteral("../NADL/oldguy.ico"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon(icon);
    setIconSize(QSize(50, 50));
    setAttribute(Qt::WA_DeleteOnClose);
    show();
}

void PushButton::doThisClicked(){
    qDebug() << "jajajaj";
}

void PushButton::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata2")) {
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

void PushButton::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata2")) {

        qDebug() << "DPB This Pos" << this->pos();
        qDebug() << "DPB Event Pos" << event->pos();

        this->move(this->pos());




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
    printf("DPB Printed This\n");
    fflush(stdout);

    QPixmap pixmap;
    PushButton *child2 = this;
    qDebug() << child2->metaObject()->className();

    if( child2 && ((QString)child2->metaObject()->className() == "QPushButton")){
        QIcon icon;
        pixmap = child2->icon().pixmap(65,65);
        qDebug() << "DPB Its valid!";
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
            child2->show();
            printf("DPB Inside4\n");
            fflush(stdout);
        } else {
             child2->close();
             printf("DPB Outside4\n");
             fflush(stdout);
        }
    }
    return;
}
