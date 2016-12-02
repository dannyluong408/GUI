#include "textbrowser.hpp"

TextBrowser::TextBrowser(QWidget *parent)
    : QTextBrowser(parent)
{
    this->setCursor(QCursor(QPixmap(":/ui/images/cursor_normal.png"),0,0));
}


void TextBrowser::mousePressEvent(QMouseEvent *mevent){
    //do something here to clear picked up spell then proceed to normal events
    emit resetCursor(0);
    QTextBrowser::mousePressEvent(mevent);
}


void TextBrowser::mouseMoveEvent(QHoverEvent *event){
    qDebug() << "Hovering over chat";
}
