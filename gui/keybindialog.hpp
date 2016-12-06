#pragma once

#include <QtWidgets>

class KeybindDialog: public QFrame
{
    Q_OBJECT
    public:
        KeybindDialog(QWidget *parent);
        //void keyReleaseEvent(QKeyEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void mousePressEvent(QMouseEvent *mevent);
        void wheelEvent(QWheelEvent *wevent);
        int num;

    signals:
        void newBind(QKeySequence newBind, int num);
        //void newMouseBind(QMouseEvent bindStr, int num);

    private:
        QLabel *info;

        QString buttonPress;
        quint32 mod;

        int count;
};
