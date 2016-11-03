#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
//#include "dragwidget.h"
#include "dragpushbutton.h"
#include "actionbar.h"
#include "bufficon.h"
#include "buffframe.h"
#include "unitframe.h"
#include "progressbar.h"
#include <time.h>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    //screens *gameScreen = new screens(this);


    ActionBar *actionBar1 = new ActionBar(ui->gameScreen);
    actionBar1->setMainBarHotkey();
    actionBar1->setButtonSpell(1,1);
    actionBar1->setButtonSpell(2,2);
    actionBar1->setButtonSpell(3,3);
    ActionBar *actionBar2 = new ActionBar(ui->gameScreen);
    actionBar1->move(350,750);
    actionBar2->move(350,800);

    BuffFrame *buffFrame;
    buffFrame = new BuffFrame(ui->gameScreen);
    buffFrame->setObjectName(QStringLiteral("buffFrame"));
    buffFrame->setMinimumSize(QSize(410, 410));
    buffFrame->setFrameShape(QFrame::StyledPanel);
    buffFrame->setFrameShadow(QFrame::Raised);
    buffFrame->setGeometry(200,150,450,450);

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

    connect(this, SIGNAL(newSize(QSize)),actionBar2,SLOT(resizeMe(QSize)));

    actionBar1->setStyleSheet("border-color:black;");
    actionBar2->setStyleSheet("border-color:black;");

    UnitFrame *playerFrame = new UnitFrame(ui->gameScreen);
    playerFrame->move(0,25);

    UnitFrame *targetFrame = new UnitFrame(ui->gameScreen);
    targetFrame->move(250,25);


    ui->gameScreen->hide();

    loginScreen = new QWidget(this);
    loginScreen->setGeometry(0,0,1200,900);
    loginScreen->show();
    loginScreen->setStyleSheet("background-color: pink");
    QPushButton *test = new QPushButton(loginScreen);
    test->setGeometry(550,400,100,100);
    test->setIconSize(QSize(100,100));
    test->setIcon(QIcon(":/ui/images/oldguy.ico"));


    connect(test,SIGNAL(clicked(bool)),this,SLOT(login()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginScreen;
}

void MainWindow::login(){
    qDebug() << "Login Sucessful!";
    loginScreen->hide();
    ui->gameScreen->show();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    if (event->oldSize().height() < 0 || event->oldSize().width() < 0){
        return;
    }
    //qDebug() << "Window Resized From" << event->oldSize() << " to " << event->size();
    emit newSize(event->size());
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
