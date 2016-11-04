#include "chatbox.h"



Chatbox::Chatbox(QWidget *parent)
    : QTextEdit(parent)
{
    setGeometry(0,700,200,200);
    viewport()->setAutoFillBackground(true);

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(255,255,255));
    setPalette(p);
    setTextColor(Qt::cyan);
}
