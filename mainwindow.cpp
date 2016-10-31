#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "dragwidget.h"
#include <time.h>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->xSlider, SIGNAL(sliderMoved(int)), this, SLOT(printValues()));
    connect(ui->ySlider, SIGNAL(sliderMoved(int)), this, SLOT(printValues()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(printValues())); //do this when button pressed
    //connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(castSpell(int)));
    connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(addButton(int)) );

    ui->random->addWidget(new DragWidget);

    ui->buttonGroup->setId(ui->slot_1,1);
    ui->buttonGroup->setId(ui->slot_2,2);
    ui->buttonGroup->setId(ui->slot_3,3);
    ui->buttonGroup->setId(ui->slot_4,4);
    ui->buttonGroup->setId(ui->slot_5,5);
    ui->buttonGroup->setId(ui->slot_6,6);
    ui->buttonGroup->setId(ui->slot_7,7);
    ui->buttonGroup->setId(ui->slot_8,8);
    ui->buttonGroup->setId(ui->slot_9,9);
    ui->buttonGroup->setId(ui->slot_10,10);

    qDebug() << ui->buttonGroup->buttons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addButton(int buttonId){

//    QPushButton *newButton;
//    newButton = new QPushButton(ui->groupBox);
//    ui->buttonGroup->addButton(newButton,buttonId);
//    newButton->setObjectName(QStringLiteral("newButton"));
//    newButton->setGeometry(QRect(5, 8, 50, 50));
//    //((buttonId - 1) * 50 ) + 5)
//    newButton->setAcceptDrops(true);
//    QIcon buttonIcon;
//    buttonIcon.addFile(QStringLiteral(":/ui/images/panda2.jpg"), QSize(50,50), QIcon::Normal, QIcon::Off);
//    newButton->setIcon(buttonIcon);
//    newButton->setAutoRepeatInterval(100);
//    newButton->show();
//    printf("Button %i Pressed. Added a Button\n",buttonId);
//    fflush(stdout);


    QList<QAbstractButton *> a =  ui->buttonGroup->buttons();
    QAbstractButton *iter;

    for(int i = 0 ; i < a.length(); i++){
       iter = a.at(i);
       if(iter->objectName() == "slot_1"){
           qDebug() << i << " :)";
           delete iter;
           break;
       }
    }



    //printf("Value:%i\n",i);

//    QPushButton *old = (QPushButton*)0xdcbda8;
//    delete old;
//    struct timespec ts;
//    ts.tv_sec = 5;
//    ts.tv_nsec = 0;
//    nanosleep(&ts,NULL);

//    delete newButton;

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
