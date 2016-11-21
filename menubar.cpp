#include "menubar.h"
#include "gamemenu.hpp"

Menubar:: Menubar(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setObjectName("menuBar");
    setGeometry(950,800,240,48);
    setAcceptDrops(false);

    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Foreground,Qt::red);
    setPalette(*palette);

     for (int i = 0 ; i < 5; i++){
         menuButton[i] = new QPushButton(this);
         menuButton[i]->setGeometry((i*48),0,48,48);
         menuButton[i]->setIconSize(QSize(48,48));
     }

    menuButton[0]->setIcon(QPixmap(":/ui/images/armor.png"));
    menuButton[0]->setObjectName("Equipment");
    menuButton[1]->setIcon(QPixmap(":/ui/images/backpack.png"));
    menuButton[1]->setObjectName("Inventory");
    menuButton[2]->setIcon(QPixmap(":/ui/images/spellbook.png"));
    menuButton[2]->setObjectName("Spells");
    menuButton[3]->setIcon(QPixmap(":/ui/images/map.png"));
    menuButton[3]->setObjectName("Map");
    menuButton[4]->setIcon(QPixmap(":/ui/images/setting.png"));
    menuButton[4]->setObjectName("Settings");

    connect(menuButton[4],SIGNAL(clicked(bool)),this,SLOT(toggleThis()));
}


void Menubar::toggleThis(){

    if(!QObject::sender()){
       qDebug() << "Error NULL!!";
       return;
    }

    QString name = QObject::sender()->objectName();
//    if (name == "Equipment"){
//    }
//    else if (name == "Inventory"){
//    }
//    else if (name == "Spells"){
//    }
//    else if (name == "Map"){
//    }
    if (name == "Settings"){
            qDebug() << "Game Menu Toggled via Menubar!";
            GameMenu *gameMenuToggle = this->parent()->findChild<GameMenu*>("gameMenu");
            if(gameMenuToggle){
                gameMenuToggle->isVisible()?
                            gameMenuToggle->hide():gameMenuToggle->show();
            }
            else{
                qDebug() << "Shouldnt happen! GameMenu not found!";
            }
    }

    else if (name == ""){
        qDebug() << "No object name set!";
    }
}

void Menubar::resizeMe(QSize newSize){ //lol what a mess fix for 1080p resolution later
//    const double scale_factor_x = 950.0 / 1200.0;
    const double scale_factor_y = 800.0 / 900.0;
    const double scale_factor_icon= 48.0/900.0;

    resize(newSize.height()*scale_factor_icon*5,
           newSize.height()*scale_factor_icon);

    for(int i = 0; i<5; i++){
        menuButton[i]->move(i*newSize.height()*scale_factor_icon,
                            0);
        menuButton[i]->resize(newSize.height()*scale_factor_icon,
                              newSize.height()*scale_factor_icon);
    }

    menuButton[0]->setIcon(QPixmap(":/ui/images/armor.png").scaled(newSize.height()*scale_factor_icon,
                                                                   newSize.height()*scale_factor_icon,
                                                                   Qt::KeepAspectRatio));
    menuButton[1]->setIcon(QPixmap(":/ui/images/backpack.png").scaled(newSize.height()*scale_factor_icon,
                                                                      newSize.height()*scale_factor_icon,
                                                                      Qt::KeepAspectRatio));
    menuButton[2]->setIcon(QPixmap(":/ui/images/spellbook.png").scaled(newSize.height()*scale_factor_icon,
                                                                       newSize.height()*scale_factor_icon,
                                                                       Qt::KeepAspectRatio));
    menuButton[3]->setIcon(QPixmap(":/ui/images/map.png").scaled(newSize.height()*scale_factor_icon,
                                                                 newSize.height()*scale_factor_icon,
                                                                 Qt::KeepAspectRatio));
    menuButton[4]->setIcon(QPixmap(":/ui/images/setting.png").scaled(newSize.height()*scale_factor_icon,
                                                                     newSize.height()*scale_factor_icon,
                                                                     Qt::KeepAspectRatio));

    move(newSize.width()-this->size().width()-10,
         newSize.height()*scale_factor_y);
    return;
}
