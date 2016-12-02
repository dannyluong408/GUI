#pragma once

#include <QtWidgets>

class GameScreen : public QWidget
{
    Q_OBJECT
public:
    GameScreen(QWidget *parent = 0);
    uint32_t getCursorID();
};
