#ifndef CHATBOX_H
#define CHATBOX_H

#pragma once

#include <QtWidgets>


class Chatbox: public QTextEdit
{
    Q_OBJECT
    public:
        Chatbox(QWidget *parent);

    public slots:
        void resizeMe(QSize size);

};


#endif // CHATBOX_H
