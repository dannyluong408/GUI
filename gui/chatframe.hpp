#pragma once

#include <QtWidgets>
#include <GUI/textedit.hpp>
#include "GUI/textbrowser.hpp"


class ChatFrame: public QFrame
{
    Q_OBJECT
    public:
        ChatFrame(QWidget *parent);
        bool inputVisible();
        void setInputVisible(bool visible);
        void setInputFocus(bool focus);

    public slots:
        void handleSend();
        void resizeMe(QSize size);
    signals:
        void resetCursor(uint32_t num);
    private:
        QTabWidget *chatTabs;
        QVector<QWidget*> chatTabFrames;
        QVector<TextBrowser*> chatBrowsers;
        TextEdit *chatInput;

};
