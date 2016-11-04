#ifndef CHATBOX_H
#define CHATBOX_H

#include <QtWidgets>


class Chatbox: public QTextEdit
{
    Q_OBJECT
    public:
        Chatbox(QWidget *parent);

};


#endif // CHATBOX_H
