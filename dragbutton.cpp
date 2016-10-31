#include <QtWidgets>

#include "dragbutton.h"

DragButton::DragButton(QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(50, 50);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    QPushButton *pushButton = new QPushButton(this);
    pushButton->setObjectName(QStringLiteral("pushButton"));
    QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
    pushButton->setSizePolicy(sizePolicy3);
    QIcon icon;
    icon.addFile(QStringLiteral("../NADL/oldguy.ico"), QSize(), QIcon::Normal, QIcon::Off);
    pushButton->setIcon(icon);
    pushButton->setIconSize(QSize(50, 50));
    pushButton->setAttribute(Qt::WA_DeleteOnClose);
    pushButton->move(25,25);


}

void DragButton::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            printf("Inside1\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("Outside1\n");
            fflush(stdout);
        }
    } else {
        event->ignore();
    }
}

void DragButton::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            printf("Inside2");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("Outside2");
            fflush(stdout);
        }
    } else {
        event->ignore();
    }
}

void DragButton::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newButton = new QLabel(this);
        newButton->setPixmap(pixmap);
        newButton->move(event->pos() - offset);
        newButton->show();
        newButton->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            printf("Inside DnD\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("Outside DnD\n");
            fflush(stdout);
        }
    } else {
        event->ignore();
    }
}

void DragButton::mousePressEvent(QMouseEvent *event)
{
    printf("Printed This old\n");
    fflush(stdout);

    QPushButton *child = static_cast<QPushButton*>(childAt(event->pos()));
    if (!child)
        return;

    printf("Hello?\n");

    QIcon icon = child->icon();
    QPixmap pixmap = icon.pixmap(icon.actualSize(QSize(51, 51)));

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

//    QPixmap tempPixmap = pixmap;
//    QPainter painter;
//    painter.begin(&tempPixmap);
//    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
//    painter.end();

    child->setIcon(pixmap);
    child->setIconSize(pixmap.rect().size());

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
        //child->show();
        printf("Inside4\n");
        fflush(stdout);
    } else {
        //child->show();
        //child->setPixmap(pixmap);
        child->close();
        printf("Outside4\n");
        fflush(stdout);
    }
}
