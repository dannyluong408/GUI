#include "popupframe.h"


PopupFrame::PopupFrame(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setGeometry(800,200,300,400);


    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Foreground,Qt::red);
    setPalette(*palette);
    setStyleSheet("background-color: blue;");

    mainLayout = new QVBoxLayout(this);
    frameTitle = new QLabel(this);
    frameTabWidget = new QTabWidget(this);
    mainLayout->addWidget(frameTitle);
    mainLayout->addWidget(frameTabWidget);

    frameTitle = new QLabel(this);
    frameTitle->resize(size().width(),frameTitle->height());
    frameTitle->setAlignment(Qt::AlignCenter);
    frameTitle->setText(QString("Spellbook"));
    frameTitle->setStyleSheet("border: 1px solid black;"
                              "background-color: cyan;"
                              "font-weight: bold;");

    for(int i=1; i<=4; i++){
        int index1 = i - 1;
        frameTabs[index1] = new QWidget();
        frameGrid[index1] = new QGridLayout(frameTabs[index1]);
        frameTabWidget->addTab(frameTabs[index1],QString("Tab %1").arg(i));
        frameTabs[index1]->setPalette(*palette);
        frameTabs[index1]->setStyleSheet("background-color: green;");

        for (int j = 1; j <= 8; j++){
            int index2 = (index1*8)+(j-1);
            spellSlotFrame[index2] = new QFrame(frameTabs[index1]);
            spellSlotFrameLayout[index2] = new QHBoxLayout(spellSlotFrame[index2]);
            spellSlot[index2] = new PushButton(spellSlotFrame[index2]);
            spellSlotDesc[index2] = new QLabel(spellSlotFrame[index2]);
            spellSlotDesc[index2]->setWordWrap(true);
            QString test = QString("Spell %1").arg(index2);
            spellSlotDesc[index2]->setText(test);
            spellSlotDesc[index2]->setStyleSheet("border: 1px solid black;");
            spellSlotFrameLayout[index2]->addWidget(spellSlot[index2]);
            spellSlotFrameLayout[index2]->addWidget(spellSlotDesc[index2]);
            frameGrid[index1]->addWidget(spellSlotFrame[index2],index2/2,index2%2);
        }


    }




}

PopupFrame::~PopupFrame(){
}

void PopupFrame::resizeMe(QSize newSize){
    const double scale_factor_x = (double)800 / (double)1200;
    const double scale_factor_y = (double)200 / (double)900;
    const double scale_factor_w = (double)300 / (double)1200;
    const double scale_factor_h = (double)400 / (double)900;
    move(newSize.width()*scale_factor_x,newSize.height()*scale_factor_y);
    resize(newSize.width()*scale_factor_w,newSize.height()*scale_factor_h);
    frameTitle->resize(size().width(),frameTitle->height());
}

void PopupFrame::toggleMe(){
    isVisible()?hide():show();
}



