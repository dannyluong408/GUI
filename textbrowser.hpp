#pragma once

#include <QtWidgets>

class TextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    TextBrowser(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *mevent);
    void mouseMoveEvent(QHoverEvent *event);

signals:
    void resetCursor(const uint32_t spellid);
};
