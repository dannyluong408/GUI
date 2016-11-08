#include "spellbook.h"

#include <QtGlobal>



SpellBook::SpellBook(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setGeometry(800,200,300,400);
    setObjectName("spellBook");

    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Foreground,Qt::red);
    setPalette(*palette);

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
        frameStack[index1] = new QStackedWidget(frameTabWidget);
        frameTabs[index1] = new QWidget(frameStack[index1]);
        frameStack[index1]->addWidget(frameTabs[index1]);
        frameGrid[index1] = new QGridLayout(frameTabs[index1]);
        frameTabWidget->addTab(frameStack[index1],QString("Tab %1").arg(i));
        frameTabs[index1]->setPalette(*palette);
        frameTabs[index1]->setStyleSheet("background-color: green;");

        for (int j = 1; j <= 10; j++){
            int index2 = (index1*10)+(j-1);
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

        if(index1 == 0){
            for(int k = 5; k <= 6; k++){
                frameTabs[k-1] = new QWidget(frameStack[index1]);
                frameStack[index1]->addWidget(frameTabs[k-1]);
                frameGrid[k-1] = new QGridLayout(frameTabs[k-1]);
                frameTabs[k-1]->setPalette(*palette);
                frameTabs[k-1]->setStyleSheet("background-color: green;");
                for (int l = 1; l <= 10; l++){
                    int index3 = ((k-1)*10)+(l-1);
                    spellSlotFrame[index3] = new QFrame(frameTabs[k-1]);
                    spellSlotFrameLayout[index3] = new QHBoxLayout(spellSlotFrame[index3]);
                    spellSlot[index3] = new PushButton(spellSlotFrame[index3]);
                    spellSlotDesc[index3] = new QLabel(spellSlotFrame[index3]);
                    spellSlotDesc[index3]->setWordWrap(true);
                    QString test = QString("Spell %1").arg(index3);
                    spellSlotDesc[index3]->setText(test);
                    spellSlotDesc[index3]->setStyleSheet("border: 1px solid black;");
                    spellSlotFrameLayout[index3]->addWidget(spellSlot[index3]);
                    spellSlotFrameLayout[index3]->addWidget(spellSlotDesc[index3]);
                    frameGrid[k-1]->addWidget(spellSlotFrame[index3],index3/2,index3%2);
                }
            }
        }
    }


    testL = new QPushButton(frameTabWidget);
    testL->setObjectName("testL");
    testR = new QPushButton(frameTabWidget);
    testR->setObjectName(("testR"));

    testL->setGeometry(195,340,40,18);
    testR->setGeometry(235,340,40,18);
    testL->setText("Left");
    testR->setText("Right");

    connect(frameTabWidget,SIGNAL(currentChanged(int)),this,SLOT(hideButtons(int)));
    connect(testL,SIGNAL(clicked(bool)),this,SLOT(pageTurn()));
    connect(testR,SIGNAL(clicked(bool)),this,SLOT(pageTurn()));

    setVisible(false);
}


void SpellBook::hideButtons(int tab){
    if(frameStack[tab]->count() <= 1){
       testL->hide();
       testR->hide();
    }
    else{
        testL->show();
        testR->show();
    }
}

void SpellBook::pageTurn(){
    QPushButton *check = qobject_cast<QPushButton*>(sender());
    const int i = frameTabWidget->currentIndex();
    if (check && check->objectName() == "testL"){
        if (frameStack[i]->currentIndex() == i){
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("Already at first page cant go left!");
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->exec();
            return;
        }
        frameStack[i]->setCurrentIndex(frameStack[i]->currentIndex()-1);\

    }
    else if (check && check->objectName() == "testR"){
        if(frameStack[i]->currentIndex() == frameStack[i]->count() - 1){
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->setText("Already at last page cant go right!");
            msgBox->exec();
            return;
        }
        frameStack[i]->setCurrentIndex(frameStack[i]->currentIndex()+1);
    }
}


SpellBook::~SpellBook(){

}



void SpellBook::resizeMe(QSize newSize){
    double scale_factor_x = (double)800 / (double)1200;
    double scale_factor_y = (double)200 / (double)900;
    double scale_factor_w = (double)300 / (double)1200;
    double scale_factor_h = (double)400 / (double)900;
    move(newSize.width()*scale_factor_x,newSize.height()*scale_factor_y);
    resize(newSize.width()*scale_factor_w,newSize.height()*scale_factor_h);
    frameTitle->resize(size().width(),frameTitle->height());


    scale_factor_x = (double)195 / (double)1200;
    scale_factor_y = (double)340 / (double)900;
    scale_factor_w = (double)40/ (double)1200;
    scale_factor_h = (double)18 / (double)900;
    const double scale_factor_offset = (double) 40 / (double)1200;

    if (frameTabWidget->findChild<QPushButton *>("testL") && frameTabWidget->findChild<QPushButton *>("testR")){
        frameTabWidget->findChild<QPushButton *>("testL")->setGeometry(newSize.width()*scale_factor_x,
                                                                       newSize.height()*scale_factor_y,
                                                                       newSize.width()*scale_factor_w,
                                                                       newSize.height()*scale_factor_h);
        frameTabWidget->findChild<QPushButton *>("testR")->setGeometry(newSize.width()*scale_factor_x+
                                                                       newSize.width()*scale_factor_offset,
                                                                       newSize.height()*scale_factor_y,
                                                                       newSize.width()*scale_factor_w,
                                                                       newSize.height()*scale_factor_h);
     }

}



