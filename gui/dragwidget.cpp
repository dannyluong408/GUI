/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "GUI/dragwidget.h"

DragWidget::DragWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(300,300);
    setMaximumSize(300,300);
    setAcceptDrops(true);

    QLabel *boatIcon = new QLabel(this);
    boatIcon->setPixmap(QPixmap(QString::fromUtf8(":/ui/images/boat.png")));
    boatIcon->move(25, 25);
    boatIcon->show();
    boatIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *carIcon = new QLabel(this);
    carIcon->setPixmap(QPixmap(QString::fromUtf8(":/ui/images/car.png")));
    carIcon->move(25, 100);
    carIcon->show();
    carIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *houseIcon = new QLabel(this);
    houseIcon->setPixmap(QPixmap(QString::fromUtf8(":/ui/images/house.png")));
    houseIcon->move(25, 175);
    houseIcon->show();
    houseIcon->setAttribute(Qt::WA_DeleteOnClose);
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
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

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
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

void DragWidget::dropEvent(QDropEvent *event)
{
    qDebug() << "Triggered";

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
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
            //if the button is the same button dont do anything
            //else transfer data
            event->setDropAction(Qt::MoveAction);
            event->accept();
            printf("dnd1 Inside DnD\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("dnd1 Outside DnD\n");
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
            printf("dnd2 Inside DnD\n");
            fflush(stdout);
        } else {
            event->acceptProposedAction();
            printf("dnd2 Outside DnD\n");
            fflush(stdout);
        }
    }
    else {
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    printf("DW Printed This\n");
    fflush(stdout);

    QPixmap pixmap;

    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    QPushButton *child2 = static_cast<QPushButton*>(childAt(event->pos()));

    if(child) qDebug() << child->metaObject()->className();
    if(child2) qDebug() << child2->metaObject()->className();

    if(child && ((QString)child->metaObject()->className() == "QLabel")){
        qDebug() << "Its valid!";

        pixmap = *child->pixmap();

        qDebug() << "Its valid1.5!";
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pixmap << QPoint(event->pos() - child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        qDebug() << "Its valid2!";
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child->pos());

        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();
        qDebug() << "Its valid3!";
        child->setPixmap(tempPixmap);
        qDebug() << "Its valid4!";

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

    else if( child2 && ((QString)child2->metaObject()->className() == "QPushButton")){
        QIcon icon;
        pixmap = child2->icon().pixmap(65,65);
        qDebug() << "Its valid1.5!";
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pixmap << QPoint(event->pos() - child2->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        qDebug() << "Its valid2!";
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child2->pos());

        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();

        qDebug() << "Its valid3!";
        //child2->setPixmap(tempPixmap);
        QIcon buttonIcon(tempPixmap);
        child2->setIcon(buttonIcon);
        child2->setIconSize(pixmap.rect().size());

        qDebug() << "Its valid4!";
        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
            child2->close();
            //child2->show();
            printf("Inside4\n");
            fflush(stdout);
        } else {
            drag->exec(Qt::MoveAction);
            //child2->show();
            //child2->setPixmap(pixmap);
            child2->close();
            printf("Outside4\n");
            fflush(stdout);
        }
    }
    return;
}
