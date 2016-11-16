#ifndef CHATBOX_H
#define CHATBOX_H

#pragma once

#include <QtWidgets>
#include <textedit.hpp>


class ChatFrame: public QFrame
{
    Q_OBJECT
    public:
        ChatFrame(QWidget *parent);
        bool inputVisible();
        void setInputVisible(bool visible);
        void toggleInputFocus(bool focus);
        void test();

    public slots:
        void handleSend();
        void resizeMe(QSize size);

    private:
        QTabWidget *chatTabs;
        QVector<QWidget*> chatTabFrames;
        QVector<QTextBrowser*> chatBrowsers;
        TextEdit *chatInput;

};


#endif // CHATBOX_H
