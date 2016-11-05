#include "popupframe.h"


PopupFrame::PopupFrame(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);

    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Foreground,Qt::red);
    setPalette(*palette);
    setStyleSheet("background-color: red;");

    QLabel *title = new QLabel(this);
    title->setGeometry(75,0,50,25);
    title->setText(QString("Spellbook"));
    title->setStyleSheet("border: 1px solid black;");
    title->show();

}


void PopupFrame::resizeMe(QSize newSize){

}

void PopupFrame::toggleMe(){
    isVisible()?hide():show();
}
