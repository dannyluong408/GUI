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
#include "chatbox.h"
#include "spellbook.h"
#include "gamemenu.h"
#include "guildframe.hpp"
#include <time.h>
#include "menubar.h"
#include "options.hpp"
#include <QDebug>
#include <QtGlobal>
#include <QHostInfo>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    //screens *gameScreen = new screens(this);

    numBars = 2;
    actionBar[0] = new ActionBar(ui->gameScreen);
    actionBar[0]->setMainBarHotkey();
    actionBar[0]->setButtonSpell(1,1);
    actionBar[0]->setButtonSpell(2,2);
    actionBar[0]->setButtonSpell(3,3);
    actionBar[1] = new ActionBar(ui->gameScreen);
    actionBar[0]->move(350,750);
    actionBar[1]->move(350,800);

//    BuffIcon *buffs[4];
//    const double scale_factor = (double)32 / (double)1080;
//    int newSize = size().height()*scale_factor;

//    for(int i = 0; i < 4 ; i++){
//        buffs[i] = new BuffIcon(playerBuffFrame);
//        buffFrame->insertBuff(buffs[i]);
//        buffs[i]->setGeometry((i*newSize),100*scale_factor,
//                              newSize,newSize);

//        switch(i%4){
//            case 0:
//                buffs[i]->setStyleSheet("border: 1px solid black");
//                break;
//            case 1:
//                buffs[i]->setStyleSheet("border: 1px solid green");
//                break;
//            case 2:
//                buffs[i]->setStyleSheet("border: 1px solid blue");
//                break;
//            case 3:
//                buffs[i]->setStyleSheet("border: 1px solid red");
//                break;
//            default:
//                buffs[i]->setStyleSheet("border: 1px solid yellow");
//                break;
//        }

//        buffs[i]->setPixmap(QPixmap(":/ui/images/oldguy.ico").scaled(newSize,newSize,Qt::KeepAspectRatio));
//        buffs[i]->setOGPix(buffs[i]->pixmap());
//    }

    actionBar[0]->setStyleSheet("border-color:black;");
    actionBar[1]->setStyleSheet("border-color:black;");

    //player+target frames
    UnitFrame *playerFrame = new UnitFrame(ui->gameScreen);
    playerFrame->move(0,10);

    UnitFrame *targetFrame = new UnitFrame(ui->gameScreen);
    targetFrame->move(275,10);

    //player buff/debuff frame
    BuffFrame *playerBuff;
    playerBuff = new BuffFrame(ui->gameScreen);
    playerBuff->setObjectName("playerBuff");
    playerBuff->move(0,95);

    BuffFrame *playerDebuff;
    playerDebuff = new BuffFrame(ui->gameScreen);
    playerBuff->setObjectName("playerDebuff");
    playerDebuff->move(0,145);

    //target buff/debuff frame
    BuffFrame *targetBuff;
    targetBuff = new BuffFrame(ui->gameScreen);
    targetBuff->setObjectName("targetBuff");
    targetBuff->move(275,95);

    BuffFrame *targetDebuff;
    targetDebuff = new BuffFrame(ui->gameScreen);
    targetBuff->setObjectName("targetDebuff");
    targetDebuff->move(275,145);

    //chatbox
    Chatbox *chat = new Chatbox(ui->gameScreen);

    //menubar
    Menubar *menuBar = new Menubar(ui->gameScreen);

    //spellbook
    SpellBook *spellBook = new SpellBook(ui->gameScreen);

    //game menu
    GameMenu *gameMenu = new GameMenu(ui->gameScreen);

    //game menu options popups
    OptionsFrame *options = new OptionsFrame(ui->gameScreen);

    //guild menu
    GuildFrame *guild_frame = new GuildFrame(ui->gameScreen);

    //connect signals for custom resize
    connect(this, SIGNAL(newSize(QSize)),playerBuff,SLOT(resizeMe(QSize)));
    connect(this, SIGNAL(newSize(QSize)),playerDebuff,SLOT(resizeMe(QSize)));
    connect(this, SIGNAL(newSize(QSize)),targetBuff,SLOT(resizeMe(QSize)));
    connect(this, SIGNAL(newSize(QSize)),targetDebuff,SLOT(resizeMe(QSize)));
    connect(this, SIGNAL(newSize(QSize)),actionBar[0],SLOT(resizeMe(QSize)));
    connect(this, SIGNAL(newSize(QSize)),actionBar[1],SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),playerFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),targetFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),menuBar,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),chat,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),spellBook,SLOT(resizeMe(QSize)));
    connect(gameMenu,SIGNAL(openThis(QString)),this,SLOT(test(QString)));
    ui->gameScreen->hide();

    loginScreen = new QWidget(this);
    loginScreen->setGeometry(0,0,1200,900);
    loginScreen->show();
    loginScreen->setStyleSheet("background-color: pink;"
                               "background-image: url(:/ui/images/anime.jpg);");

    qDebug() << "Looking for IP of login.sniperdad.com ...";
    QHostInfo::lookupHost("login.sniperdad.com",this,SLOT(lookedUp(QHostInfo)));


    QPushButton *test = new QPushButton(loginScreen);
    test->setGeometry(550,400,100,100);
    test->setIconSize(QSize(100,100));
    test->setIcon(QIcon(":/ui/images/oldguy.ico"));

    connect(test,SIGNAL(clicked(bool)),this,SLOT(login()));

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    //this->timer.start(1); //call update every 1us
}

void MainWindow::update(){

}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginScreen;
}

void MainWindow::test(QString name){
    if(name == "Help"){

    }
    else if (name == "Options"){
        OptionsFrame *options = findChild<OptionsFrame*>("optionsFrame");
        findChild<GameMenu*>("gameMenu")->setVisible(false);
        options->show();
    }
    else if (name == "Interface"){

    }
    else if (name == "Key Bindings"){

    }
    else if (name == "Macros"){

    }
    else if (name == "Logout"){

    }
    else if (name == "Exit Game"){

    }
}

void MainWindow::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    foreach (const QHostAddress &address, host.addresses())
        qDebug() << "Found address:" << address.toString();
}
void MainWindow::login(){
    qDebug() << "Login Sucessful!";
    loginScreen->hide();
    ui->gameScreen->show();
    ui->gameScreen->setFocus();
    ui->openGLWidget->hide();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    if (event->oldSize().height() < 0 || event->oldSize().width() < 0){
        return;
    }
    //qDebug() << "Window Resized From" << event->oldSize() << " to " << event->size();
    emit newSize(event->size());

    //resize openglwidget too ? need to resize other stuff inside this when init'd
    ui->openGLWidget->resize(event->size());

    //temporarily keep action bar repositions here cause noob
    double scale_factor_x = (double)350 / (double)1080;
    double scale_factor_y = (double)750 / (double)1080;
    const double scale_height = (double)50 / (double)1080;

    for (int i=0; i< numBars; i++){
        actionBar[i]->move(event->size().width()*scale_factor_x,
                           event->size().height()*scale_factor_y +
                          (event->size().height()*scale_height*i));
    }
}


void MainWindow::castSpell(int buttonPos){
    printf("Casting from Slot %i\n", buttonPos);
    fflush(stdout);
    //figure out current data of button
    //check for CD / target
    //handle it
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
      case Qt::Key_P:{
          qDebug() << "Spellbook Toggled!";
          SpellBook *spellBookToggle = findChild<SpellBook*>("spellBook");
          if(spellBookToggle){
              spellBookToggle->isVisible()?
                          spellBookToggle->hide():spellBookToggle->show();
          }
          else{
              qDebug() << "Shouldnt happen! GameMenu not found!";
          }
          break;
    }
      case Qt::Key_Escape:{
          qDebug() << "Game Menu Toggled via Hotkey ESC!";
          if (findChild<OptionsFrame*>("optionsFrame")->isVisible()){
              findChild<OptionsFrame*>("optionsFrame")->hide();
          }
          else{
              if(findChild<GameMenu*>("gameMenu")){
              findChild<GameMenu*>("gameMenu")->isVisible()?
                          findChild<GameMenu*>("gameMenu")->hide():
                          findChild<GameMenu*>("gameMenu")->show();
              }
              else{
                  qDebug() << "Shouldnt happen! GameMenu not found!";
              }
          }
          break;
    }
//      case Qt::Key_F1:{
//        break;
//    }

     case Qt::Key_C:{
        qDebug() << "Guild Frame Toggled via Hotkey C!";
        GuildFrame *guildFrameToggle = findChild<GuildFrame*>("guildFrame");
        if(guildFrameToggle){
            guildFrameToggle->isVisible()?
                        guildFrameToggle->setVisible(false):guildFrameToggle->show();
        }
        else{
            qDebug() << "Shouldnt happen! GuildFrame not found!";
        }
        break;
    }
      case Qt::Key_Enter:
          //enter will open and close chatbox
          break;
      default:
          QWidget::keyPressEvent(event);
    }
}
