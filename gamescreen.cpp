#include "gamescreen.hpp"
#include "mainwindow.h"

GameScreen::GameScreen(QWidget *parent)
    : QWidget(parent)
{

}


uint32_t GameScreen::getCursorID(){
    MainWindow *info = (MainWindow*)parent();
    qDebug() << "Grabbing ID:" << info->cursorID;
    return info->cursorID;
}
