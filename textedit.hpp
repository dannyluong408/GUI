#ifndef CHATINPUT_HPP
#define CHATINPUT_HPP

#pragma once

#include <QtWidgets>


class TextEdit: public QTextEdit
{
    Q_OBJECT
    public:
        TextEdit(QWidget *parent);

    signals:
        void send();

    private:
        void keyPressEvent(QKeyEvent *event);


};

#endif // CHATINPUT_HPP
