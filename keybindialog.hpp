#ifndef KEYDIALOG_HPP
#define KEYDIALOG_HPP

#pragma once

#include <QtWidgets>


class KeybindDialog: public QFrame
{
    Q_OBJECT
    public:
        KeybindDialog(QWidget *parent);
        void keyReleaseEvent(QKeyEvent *event);
        //void keyPressEvent(QKeyEvent *event);
        void parseKey(QString key);
        int num;

    signals:
        void newBind(QKeySequence newBind, int num);

    private:
        QLabel *info;
        QString keyPress;
        int count;
};


#endif // KEYDIALOG_HPP
