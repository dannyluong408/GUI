#include "GUI/gamescreen.hpp"
#include "GUI/mainwindow.h"

GameScreen::GameScreen(QWidget *parent)
    : QWidget(parent)
{

}

void GameScreen::dragEnterEvent(QDragEnterEvent *event){
    event->accept();
}
