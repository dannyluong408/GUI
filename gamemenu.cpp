#include "gamemenu.h"



GameMenu::GameMenu(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setGeometry(550,350,100,220);
    setObjectName("gameMenu");

    QLabel *frameLabel = new QLabel(this);
    frameLabel->setGeometry(0,0,100,20);
    frameLabel->setText("Game Menu");
    frameLabel->setAlignment(Qt::AlignCenter);
    frameLabel->setStyleSheet("border: 1px solid black;");

    QWidget *layoutFrame = new QWidget(this);
    layoutFrame->setGeometry(0,20,100,200);

    mainLayout = new QVBoxLayout(layoutFrame);
    mainLayout->setContentsMargins(1,1,1,1);
    mainLayout->setSpacing(1);

    for(int i = 0; i < 8; i++){
        options[i] = new QPushButton(this);
        options[i]->resize(100,25);
        QString objName = QString("option%1").arg(i);
        options[i]->setObjectName(objName);
        mainLayout->addWidget(options[i]);
        connect(options[i],SIGNAL(clicked(bool)),this,SLOT(openOption()));
    }

    options[0]->setText("Help");
    options[1]->setText("Options");
    options[2]->setText("Interface");
    options[3]->setText("Key Bindings");
    options[4]->setText("Macros");
    options[5]->setText("Logout");
    options[6]->setText("Exit Game");
    options[7]->setText("Return to Game");

    setVisible(false);
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
            emit(openThis("Interface"));
            break;
        case 3:
            emit(openThis("Key Bindings"));
            break;
        case 4:
            emit(openThis("Macros"));
            break;
        case 5:
            emit(openThis("Logout"));
            break;
        case 6:
            emit(openThis("Exit Game"));
            break;
        case 7:
            this->setVisible(false);
            break;
    }
}
