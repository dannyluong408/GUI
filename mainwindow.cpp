#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
//#include "dragwidget.h"
#include "dragpushbutton.h"
#include "actionbar.h"
#include "bufficon.h"
#include "buffframe.h"
#include <time.h>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    connect(ui->xSlider, SIGNAL(sliderMoved(int)), this, SLOT(printValues()));
    connect(ui->ySlider, SIGNAL(sliderMoved(int)), this, SLOT(printValues()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(printValues())); //do this when button pressed
    //connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(castSpell(int)));
    //connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(addButton(int)) );

    ui->actionBarLayout->setAlignment(Qt::AlignAbsolute);

    ActionBar *actionBar1 = new ActionBar(this);
    ui->actionBarLayout->addWidget(actionBar1);
    actionBar1->setMainBarHotkey();

    actionBar1->setButtonSpell(1,1);
    actionBar1->setButtonSpell(2,2);
    actionBar1->setButtonSpell(3,3);

    BuffFrame *buffFrame;
    buffFrame = new BuffFrame(ui->centralWidget);
    buffFrame->setObjectName(QStringLiteral("buffFrame"));
    buffFrame->setMinimumSize(QSize(410, 410));
    buffFrame->setFrameShape(QFrame::StyledPanel);
    buffFrame->setFrameShadow(QFrame::Raised);
    buffFrame->setGeometry(200,100,450,450);

    BuffIcon *buffs[4];
    QPixmap pix(":/ui/images/oldguy.ico");


    qDebug() << size();

    int width = size().width();
    int height = size().height();

    qDebug() << width << "," << height;

    const double scale_factor = (double)32 / (double)1080;
    int newSize = size().height()*scale_factor;

    for(int i = 0; i < 4 ; i++){
        buffs[i] = new BuffIcon(buffFrame);
        buffFrame->insertBuff(buffs[i]);
        buffs[i]->setGeometry((i*newSize),100*scale_factor,
                              newSize,newSize);


        switch(i%4){
            case 0:
                buffs[i]->setStyleSheet("border: 1px solid black");
                break;
            case 1:
                buffs[i]->setStyleSheet("border: 1px solid green");
                break;
            case 2:
                buffs[i]->setStyleSheet("border: 1px solid blue");
                break;
            case 3:
                buffs[i]->setStyleSheet("border: 1px solid red");
                break;
            default:
                buffs[i]->setStyleSheet("border: 1px solid yellow");
                break;
        }

        buffs[i]->setPixmap(QPixmap(":/ui/images/oldguy.ico").scaled(newSize,newSize,Qt::KeepAspectRatio));
        buffs[i]->setOGPix(buffs[i]->pixmap());
    }

    for(int test = 0; test< 4; test++){
        connect(this, SIGNAL(newSize(QSize)),buffs[test],SLOT(resizeMe(QSize)));
    }

    connect(this, SIGNAL(newSize(QSize)),buffFrame,SLOT(resizeMe(QSize)));
    connect(this, SIGNAL(newSize(QSize)),actionBar1,SLOT(resizeMe(QSize)));
    ActionBar *actionBar2 = new ActionBar(this);
    connect(this, SIGNAL(newSize(QSize)),actionBar2,SLOT(resizeMe(QSize)));




    ui->actionBarLayout->addWidget(actionBar2);
    actionBar1->setStyleSheet("border-color:black;");
    actionBar2->setStyleSheet("border-color:black;");

    ui->chatLayout->setAlignment(Qt::AlignLeft);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event){
    if (event->oldSize().height() < 0 || event->oldSize().width() < 0){
        return;
    }
    qDebug() << "Window Resized From" << event->oldSize() << " to " << event->size();
    emit newSize(event->size());
}

void MainWindow::printValues(){
    printf("Slider Change Detected! Values are: X:%i, Y:%i\n",ui->xSlider->value(),ui->ySlider->value());
    fflush(stdout);
}

void MainWindow::castSpell(int buttonPos){
    printf("Casting from Slot %i\n", buttonPos);
    fflush(stdout);
    //figure out current data of button
    //check for CD / target
    //handle it
}


//bool MainWindow::eventFilter(QObject *obj, QEvent *event)
//{
//  if (obj == ui->chat_input) {
//     if (event->type() == QEvent::KeyPress) {
//         QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//        if (keyEvent->key() == Qt::Key_Tab)
//        {
//            if(ui->chat_input->hasSelectedText() == false){
//                return false;
//            }
//            //do what you need;
//            emit tabPressed();
//            return true;
//        }
//        else if (keyEvent->key() == Qt::Key_Up)
//        {
//            emit upArrow();
//            return true;
//        }
//        else if(keyEvent->key() == Qt::Key_Down)
//        {
//            emit downArrow();
//            return true;
//        }
//        if ((keyEvent->key()==Qt::Key_Enter) || (keyEvent->key()==Qt::Key_Return) )
//        {
//            if(ui->chat_input->hasSelectedText() == false){
//                return false;
//            }
//            //do what you need;
//            emit enterPressed();
//            return true;
//        }
//     }
//  }
//     // pass the event on to the parent class
//     return QMainWindow::eventFilter(obj, event);
//}
