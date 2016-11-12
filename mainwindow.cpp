#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
//#include "dragwidget.h"
#include "dragpushbutton.h"
#include "actionbar.h"
#include "bufficon.h"
#include "targetbuffframe.hpp"
#include "playerbuffframe.hpp"
#include "unitframe.h"
#include "progressbar.h"
#include "chatbox.h"
#include "spellbook.h"
#include "gamemenu.h"
#include "guildframe.hpp"
#include "partyframe.hpp"
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

    //action bars
    numBars = 2;
    actionBar[0] = new ActionBar(ui->gameScreen);
    actionBar[1] = new ActionBar(ui->gameScreen);
    actionBar[0]->move(350,800);
    actionBar[1]->move(350,850);

    //test stuff for action bars -- remove later
    actionBar[0]->setMainBarHotkey();
    actionBar[0]->setButtonSpell(1,1);
    actionBar[0]->setButtonSpell(2,2);
    actionBar[0]->setButtonSpell(3,3);
    actionBar[0]->setButtonSpell(1,4);
    actionBar[0]->setButtonSpell(2,5);
    actionBar[0]->setButtonSpell(3,6);
    actionBar[0]->setButtonSpell(1,7);
    actionBar[0]->setButtonSpell(2,8);
    actionBar[0]->setButtonSpell(3,9);
    actionBar[0]->setButtonSpell(1,10);

    //player+target frames
    UnitFrame *playerFrame = new UnitFrame(ui->gameScreen);
    playerFrame->setObjectName("playerFrame");
    playerFrame->move(12.5,12.5);

    UnitFrame *targetFrame = new UnitFrame(ui->gameScreen);
    targetFrame->setObjectName("targetFrame");
    targetFrame->move(287.5,12.5);

    //party frame
    PartyFrame *partyFrame = new PartyFrame(ui->gameScreen);
    partyFrame->setObjectName("partyFrame");
    partyFrame->move(12.5,137.5);

    //player buff/debuff frame
    PlayerBuffFrame *playerBuff;
    playerBuff = new PlayerBuffFrame(ui->gameScreen);
    playerBuff->setObjectName("playerBuff");
    playerBuff->move(767.5,12.5);


    PlayerBuffFrame *playerDebuff;
    playerDebuff = new PlayerBuffFrame(ui->gameScreen);
    playerDebuff->setObjectName("playerDebuff");
    playerDebuff->setAsDebuff(true);
    playerDebuff->move(767.5,56.5);


    //target buff/debuff frame
    TargetBuffFrame *targetBuff;
    targetBuff = new TargetBuffFrame(ui->gameScreen);
    targetBuff->setObjectName("targetBuff");
    targetBuff->move(287.5,117.5);

    TargetBuffFrame *targetDebuff;
    targetDebuff = new TargetBuffFrame(ui->gameScreen);
    targetDebuff->setObjectName("targetDebuff");
    targetDebuff->setAsDebuff(true);
    targetDebuff->move(287.5,144.5);

    //chatbox
    Chatbox *chat = new Chatbox(ui->gameScreen);

    //menubar
    Menubar *menuBar = new Menubar(ui->gameScreen);

    //spellbook
    SpellBook *spellBook = new SpellBook(ui->gameScreen);

    //guild menu
    GuildFrame *guild_frame = new GuildFrame(ui->gameScreen);

    //game menu
    GameMenu *gameMenu = new GameMenu(ui->gameScreen);

    //game menu options popups
    OptionsFrame *options = new OptionsFrame(ui->gameScreen);


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
    connect(this,SIGNAL(newSize(QSize)),partyFrame,SLOT(resizeMe(QSize)));

    //hide screen + login screen
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


    //our "constantly calling update function stuff"
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

    ui->gameScreen->resize(event->size());
    //resize openglwidget too ? need to resize other stuff inside this when init'd
    ui->openGLWidget->resize(event->size());

    //temporarily keep action bar repositions here cause noob
    double scale_factor_x = (double)350 / (double)1200;
    double scale_factor_y = (double)800 / (double)900;
    const double scale_height = (double)50 / (double)900;

    for (int i=0; i< numBars; i++){
        actionBar[i]->move(event->size().width()*scale_factor_x,
                           event->size().height()*scale_factor_y +
                          (event->size().height()*scale_height*i));
    }


    scale_factor_x = 950 / 1200.0;
    scale_factor_y = 800 / 900.0;

    if(findChild<Menubar*>("menuBar")){
        findChild<Menubar*>("menuBar")->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);
    }
    else{
        qDebug() << "Shouldn't happen, playerFrame not found";
    }

    scale_factor_x = 12.5 / 1200.0;
    scale_factor_y = 12.5 / 900.0;

    if(findChild<UnitFrame*>("playerFrame")){
        findChild<UnitFrame*>("playerFrame")->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);
    }
    else{
        qDebug() << "Shouldn't happen, playerFrame not found";
    }

    scale_factor_x = (double)287.5 / (double) 1200;

    if(findChild<UnitFrame*>("targetFrame")){
        findChild<UnitFrame*>("targetFrame")->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);
    }
    else{
        qDebug() << "Shouldn't happen, targetFrame not found";
    }


    scale_factor_x = (double)12.5 / (double) 1200;
    scale_factor_y = (double)137.5 / (double) 900;

    if(findChild<PartyFrame*>("partyFrame")){
        findChild<PartyFrame*>("partyFrame")->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);
    }
    else{
        qDebug() << "Shouldn't happen, partyFrame not found";
    }

    scale_factor_x = (double)767.5 / (double) 1200;
    scale_factor_y = (double)12.5 / (double) 900;

    if(findChild<PlayerBuffFrame*>("playerBuff")){
        findChild<PlayerBuffFrame*>("playerBuff")->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);
    }
    else{
        qDebug() << "Shouldn't happen, partyFrame not found";
    }

    scale_factor_y = (double)56.5 / (double) 900;

    if(findChild<PlayerBuffFrame*>("playerDebuff")){
        findChild<PlayerBuffFrame*>("playerDebuff")->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);
    }
    else{
        qDebug() << "Shouldn't happen, partyFrame not found";
    }

    scale_factor_x = (double)287.5 / (double) 1200;
    scale_factor_y = (double)117.5 / (double) 900;

    if(findChild<TargetBuffFrame*>("targetBuff")){
        findChild<TargetBuffFrame*>("targetBuff")->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);
    }
    else{
        qDebug() << "Shouldn't happen, partyFrame not found";
    }

    scale_factor_y = (double)144.5 / (double) 900;

    if(findChild<TargetBuffFrame*>("targetDebuff")){
        findChild<TargetBuffFrame*>("targetDebuff")->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);
    }
    else{
        qDebug() << "Shouldn't happen, partyFrame not found";
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
                  if(findChild<SpellBook*>("spellBook")->isVisible()){
                      findChild<SpellBook*>("spellBook")->hide();
                  }
                  if(findChild<GuildFrame*>("guildFrame")->isVisible()){
                      findChild<GuildFrame*>("guildFrame")->hide();
                  }
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
