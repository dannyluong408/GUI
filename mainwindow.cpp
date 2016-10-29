#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include "dragwidget.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->xSlider, SIGNAL(sliderMoved(int)), this, SLOT(printValues()));
    connect(ui->ySlider, SIGNAL(sliderMoved(int)), this, SLOT(printValues()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(printValues())); //do this when button pressed

    QLabel *boatIcon2 = new QLabel(this);
    boatIcon2->setPixmap(QPixmap(QString::fromUtf8(":/ui/images/panda.jpg")));
    boatIcon2->move(50, 50);
    boatIcon2->show();
    boatIcon2->setAttribute(Qt::WA_DeleteOnClose);

    DragWidget *DragWidget1;
    DragWidget *DragWidget2;
    DragWidget1 = new DragWidget(ui->centralWidget);
    DragWidget2 = new DragWidget(ui->centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printValues(){
    printf("Slider Change Detected! Values are: X:%i, Y:%i\n",ui->xSlider->value(),ui->ySlider->value());
    fflush(stdout);
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
