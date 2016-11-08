#ifndef CHATBOX_H
#define CHATBOX_H

#pragma once

#include <QtWidgets>


class Chatbox: public QFrame
{
    Q_OBJECT
    public:
        Chatbox(QWidget *parent);

    public slots:
        void resizeMe(QSize size);

    private:
        QVBoxLayout *mainLayout;
        QTabWidget *chatTabs;
        QVector<QWidget*> chatTabFrames;
        QTextEdit *chatInput;

};


#endif // CHATBOX_H
