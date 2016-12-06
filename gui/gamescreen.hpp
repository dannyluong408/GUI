#pragma once

#include <QtWidgets>

class GameScreen : public QWidget
{
    Q_OBJECT
public:
    GameScreen(QWidget *parent = 0);
    uint32_t getCursorID();

    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
};
