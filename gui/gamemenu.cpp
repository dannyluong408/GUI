#include "GUI/gamemenu.hpp"



GameMenu::GameMenu(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setGeometry(550,380,100,145);
    setObjectName("gameMenu");

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    QLabel *frameLabel = new QLabel(this);
    frameLabel->setGeometry(0,0,100,20);
    frameLabel->setText("Game Menu");
    frameLabel->setAlignment(Qt::AlignCenter);
    frameLabel->setStyleSheet("border: 1px solid black;");

    QFrame *buttonFrame = new QFrame(this);
    buttonFrame->setGeometry(0,20,100,125);

    mainLayout->addWidget(frameLabel);
    mainLayout->addWidget(buttonFrame);

    buttonLayout = new QVBoxLayout(buttonFrame);
    buttonLayout->setContentsMargins(0,0,0,0);
    buttonLayout->setSpacing(0);

    for(int i = 0; i < 5; i++){
        options[i] = new QPushButton(this);
        options[i]->resize(100,25);
        QString objName = QString("option%1").arg(i);
        options[i]->setObjectName(objName);
        buttonLayout->addWidget(options[i]);
        connect(options[i],SIGNAL(clicked(bool)),this,SLOT(openOption()));
    }

    options[0]->setText("Help");
    options[1]->setText("Options");
    options[2]->setText("Logout");
    options[3]->setText("Exit Game");
    options[4]->setText("Return to Game");

    setVisible(false);
}


void GameMenu::resizeMe(QSize newSize){
    if (newSize == this->size()){
        qDebug() << "returned";
        return;
    }

    double scale_factor_w = 100.0/900.0;
    double scale_factor_h = 145.0/900.0;

    this->resize(newSize.height()*scale_factor_w,
           newSize.height()*scale_factor_h);

    this->move(newSize.width()/2.0 - this->width()/2.0,
               newSize.height()/2.0 - this->height()/2.0);
}

void GameMenu::openOption(){
    QString name = sender()->objectName();
    name.remove(QString("option"));

    switch(name.toInt()){
        case 0:
            emit(openThis("Help"));
            break;
        case 1:
            emit(openThis("Options"));
            break;
        case 2:
            emit(openThis("Logout"));
            break;
        case 3:
            emit(openThis("Exit Game"));
            break;
        case 4:
            this->setVisible(false);
            break;
    }
}


