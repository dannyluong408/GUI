#include "mainwindow.h"






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    //action bars
    numBars = 2;
    actionBar[0] = new ActionBar(ui->gameScreen);
    actionBar[0]->move(350,800);
    actionBar[0]->setIndex(0);
    actionBar[1] = new ActionBar(ui->gameScreen);
    actionBar[1]->move(350,850);
    actionBar[1]->setIndex(1);

//    //test stuff for action bars -- remove later
//    actionBar[0]->setButtonSpell(1,1);
//    actionBar[0]->setButtonSpell(2,2);
//    actionBar[0]->setButtonSpell(3,3);
//    actionBar[0]->setButtonSpell(1,4);
//    actionBar[0]->setButtonSpell(2,5);
//    actionBar[0]->setButtonSpell(3,6);
//    actionBar[0]->setButtonSpell(1,7);
//    actionBar[0]->setButtonSpell(2,8);
//    actionBar[0]->setButtonSpell(3,9);
//    actionBar[0]->setButtonSpell(1,10);

    //player+target frames
    playerFrame = new UnitFrame(ui->gameScreen);
    playerFrame->setObjectName("playerFrame");
    playerFrame->move(12.5,12.5);

    targetFrame = new UnitFrame(ui->gameScreen);
    targetFrame->setObjectName("targetFrame");
    targetFrame->move(287.5,12.5);

    //party frame
    partyFrame = new PartyFrame(ui->gameScreen);
    partyFrame->setObjectName("partyFrame");
    partyFrame->move(12.5,137.5);

    //player buff/debuff frame
    playerBuff = new PlayerBuffFrame(ui->gameScreen);
    playerBuff->setObjectName("playerBuff");
    playerBuff->move(767.5,12.5);

    playerDebuff = new PlayerBuffFrame(ui->gameScreen);
    playerDebuff->setObjectName("playerDebuff");
    playerDebuff->setAsDebuff(true);
    playerDebuff->move(767.5,56.5);


    //target buff/debuff frame
    targetBuff = new TargetBuffFrame(ui->gameScreen);
    targetBuff->setObjectName("targetBuff");
    targetBuff->move(287.5,117.5);

    targetDebuff = new TargetBuffFrame(ui->gameScreen);
    targetDebuff->setObjectName("targetDebuff");
    targetDebuff->setAsDebuff(true);
    targetDebuff->move(287.5,144.5);

    //chatbox
    chatFrame = new ChatFrame(ui->gameScreen);

    //menubar
    menuBar = new Menubar(ui->gameScreen);

    //spellbook
    spellBook = new SpellBook(ui->gameScreen);

    //guild menu
    guildFrame = new GuildFrame2(ui->gameScreen);

    //honor menu
    honorFrame = new HonorFrame(ui->gameScreen);

    //game menu
    gameMenu = new GameMenu(ui->gameScreen);

    //game menu options popups
    optionsMenu = new OptionsFrame(ui->gameScreen);

    //game menu keybind popup
    //KeybindMenu *keybindMenu = new KeybindMenu(ui->gameScreen);

    //spellbook test stuff delete later
    spellBook->setSlotSpell(0,1);
    spellBook->setSlotSpell(1,2);
    spellBook->setSlotSpell(2,3);

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
    connect(this,SIGNAL(newSize(QSize)),chatFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),spellBook,SLOT(resizeMe(QSize)));
    connect(gameMenu,SIGNAL(openThis(QString)),this,SLOT(openOption(QString)));
    connect(this,SIGNAL(newSize(QSize)),partyFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),guildFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),honorFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),gameMenu,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),optionsMenu,SLOT(resizeMe(QSize)));

    ui->openGLWidget->hide();
    //hide screen + login screen
    ui->gameScreen->hide();

    loginScreen = new QWidget(this);
    loginScreen->setGeometry(0,0,1200,900);
    loginScreen->show();
    loginScreen->setStyleSheet("background-color: pink;"
                               "background-image: url(:/ui/images/anime.jpg);");


    qDebug() << "Looking for IP of login.sniperdad.com ...";
    QHostInfo::lookupHost("login.sniperdad.com",this,SLOT(lookedUp(QHostInfo)));

    loginButton = new QPushButton(loginScreen);
    loginButton->setGeometry(550,400,100,100);
    loginButton->setIconSize(QSize(100,100));
    loginButton->setIcon(QIcon(":/ui/images/oldguy.ico"));

    //temp for now to ignore login screen
    login();

    //our "constantly calling update function stuff"
//    connect(loginButton,SIGNAL(clicked(bool)),this,SLOT(login()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    //this->timer.start(1); //call update every 1us

    // Keybind/Shortcut Stuff
    keybindMapper = new QSignalMapper(this);
    connect(keybindMapper,SIGNAL(mapped(int)),this,SLOT(keybindSlot(int)));
    for(int i=0; i<KEYBINDCOUNT; i++){
        shortcut[i] = new QShortcut(this);
        connect(shortcut[i],SIGNAL(activated()),keybindMapper,SLOT(map()));
        keybindMapper->setMapping(shortcut[i],i);
    }

    //init keybinds on load check for file, else default
    connect(this,SIGNAL(pushKeybinds(QString*)),optionsMenu,SLOT(updateKeybinds(QString*)));
    connect(optionsMenu,SIGNAL(disableShortcuts()),this,SLOT(disableShortcuts()));
    connect(optionsMenu,SIGNAL(enableShortcuts()),this,SLOT(enableShortcuts()));
    connect(optionsMenu,SIGNAL(newBindSend(QKeySequence,int)),this,SLOT(newBindRecv(QKeySequence,int)));
    connect(optionsMenu,SIGNAL(saveBinds()),this,SLOT(saveKeybinds()));
    connect(optionsMenu,SIGNAL(defaultBinds()),this,SLOT(defaultKeybinds()));

    qDebug() << "Initializing Keybinds";
    initKeybinds();
    loadActionBars();
    qDebug() << "Keybinds Complete";
    //connect(optionsMenu,SIGNAL()

}

void MainWindow::defaultKeybinds(){
    initDefaultKeybinds();
}

void MainWindow::newBindRecv(QKeySequence newKeybind, int num){
    qDebug() << "Setting shortcut:" << num << " to "<< newKeybind.toString();
    shortcut[num]->setKey(newKeybind);
}

void MainWindow::disableShortcuts(){
    for (int i = 0; i<KEYBINDCOUNT; i++){
        shortcut[i]->setEnabled(false);
    }
}

void MainWindow::enableShortcuts(){
    for (int i = 0; i<KEYBINDCOUNT; i++){
        shortcut[i]->setEnabled(true);
    }
}

void MainWindow::togglePane(int pane){
    using namespace Keybinds;
    switch(pane){
        case SPELLBOOK:{
            spellBook->isVisible()? spellBook->setVisible(false):spellBook->show();
            break;
        }
        case CLAN:{
            guildFrame->isVisible()? guildFrame->setVisible(false):guildFrame->show();
            break;
        }
        case HONOR:{
            qDebug() << "Honor Frame Toggled via Hotkey H!";
            honorFrame->isVisible()? honorFrame->setVisible(false):honorFrame->show();
            break;
        }
        case MAINMENU:{
            qDebug() << "Escape Hotkey Procced";
            if (optionsMenu->isVisible()){
                optionsMenu->setVisible(false);
                break;
            }
            else{
                if(guildFrame->isVisible()){
                    guildFrame->hide();
                }
                if(honorFrame->isVisible()){
                    honorFrame->hide();
                }
                if(spellBook->isVisible()){
                    spellBook->hide();
                }
                gameMenu->isVisible()? gameMenu->setVisible(false):gameMenu->show();
                break;
            }
        }
        case CHARACTER:{
            break;
        }
        case MACRO:{
            break;
        }
        case SOCIAL:{
            break;
        }
        case MAP:{
            break;
        }
    }
}

void MainWindow::targetingBind(int target){
    qDebug() << "Targeting In Progress" << target;
}
void MainWindow::cameraBind(int option){
    qDebug() << "CameraBind In Progress" << option;
}
void MainWindow::toggleAttack(){
    qDebug() << "Toggle Attack In Progress";
}

void MainWindow::toggleChat(){
    if (chatFrame->inputVisible()){
        chatFrame->setInputFocus(false);
        chatFrame->setInputVisible(false);
    }
    else{
        chatFrame->setInputFocus(true);
        chatFrame->setInputVisible(true);
    }
}

void MainWindow::whisper(int type){
    qDebug() << "Whisper feature In Progress" << type;
}

void MainWindow::screenshot(){
     qDebug() << "Screenshot feature In Progress";
}

void MainWindow::movePlayer(int direction){
        using namespace Keybinds;
    switch(direction){
        case FORWARD:
            break;
        case BACKWARD:
            break;
        case TURN_LEFT:
            break;
        case TURN_RIGHT:
            break;
        case MOVE_LEFT:
            break;
        case MOVE_RIGHT:
            break;
        case JUMP:
            break;
        default:
            qDebug() << "Bad movePlayer direction";
            break;
    }
}

void MainWindow::keybindSlot(int id){ //functions get mapped here
    qDebug() << id << "Emitted!";
    switch(id){
        //move functions
        case 0:{
            movePlayer(Keybinds::FORWARD);
            break;
        }
        case 1:{
            movePlayer(Keybinds::BACKWARD);
             break;
        }
        case 2:{
            movePlayer(Keybinds::TURN_LEFT);
            break;
        }
        case 3:{
            movePlayer(Keybinds::TURN_RIGHT);
            break;
        }
        case 4:{
            movePlayer(Keybinds::MOVE_LEFT);
            break;
        }
        case 5:{
            movePlayer(Keybinds::MOVE_RIGHT);
            break;
        }
        case 6:{
            movePlayer(Keybinds::JUMP);
            break;
        }
        case 7:{
            toggleAttack();
            break;
        }
        case 8:{ //targeting 0
            targetingBind(Keybinds::TARGET_NEAREST_ENEMY);
            break;
        }
        case 9:{
            targetingBind(Keybinds::TARGET_PREVIOUS_ENEMY);
            break;
        }
        case 10:{
            targetingBind(Keybinds::TARGET_NEAREST_ENEMY_PLAYER);
            break;
        }
        case 11:{
            targetingBind(Keybinds::TARGET_PREVIOUS_ENEMY_PLAYER);
            break;
        }
        case 12:{
            targetingBind(Keybinds::TARGET_NEAREST_FRIENDLY_PLAYER);
            break;
        }
        case 13:{//5
            targetingBind(Keybinds::TARGET_PREVIOUS_ENEMY_PLAYER);
            break;
        }
        case 14:{
            targetingBind(Keybinds::TARGET_SELF);
            break;
        }
        case 15:{
            targetingBind(Keybinds::TARGET_PARTY_MEMBER_1);
            break;
        }
        case 16:{
            targetingBind(Keybinds::TARGET_PARTY_MEMBER_2);
            break;
        }
        case 17:{
            targetingBind(Keybinds::TARGET_PARTY_MEMBER_3);
            break;
        }
        case 18:{//10
            targetingBind(Keybinds::TARGET_PARTY_MEMBER_4);
            break;
        }
        case 19:{
            targetingBind(Keybinds::TARGET_PET);
            break;
        }
        case 20:{
            targetingBind(Keybinds::TARGET_PARTY_PET_1);
            break;
        }
        case 21:{
            targetingBind(Keybinds::TARGET_PARTY_PET_2);
            break;
        }
        case 22:{
            targetingBind(Keybinds::TARGET_PARTY_PET_3);
            break;
        }
        case 23:{
            targetingBind(Keybinds::TARGET_PARTY_PET_4);
            break;
        }
        case 24:{
            targetingBind(Keybinds::ASSIST_TARGET);
            break;
        }
        case 25:{
            targetingBind(Keybinds::TOGGLE_NAMEPLATES);
            break;
        }
        case 26:{
            targetingBind(Keybinds::TOGGLE_FRIENDLY_NAMEPLATES);
            break;
        }
        case 27:{
            targetingBind(Keybinds::SET_FOCUS);
            break;
        }
        case 28:{//20
            targetingBind(Keybinds::FOCUS_ARENA_1);
            break;
        }
        case 29:{
            targetingBind(Keybinds::FOCUS_ARENA_2);
            break;
        }
        case 30:{
            targetingBind(Keybinds::FOCUS_ARENA_3);
            break;
        }
        case 31:{
            targetingBind(Keybinds::FOCUS_ARENA_4);
            break;
        }
        case 32:{
            targetingBind(Keybinds::FOCUS_ARENA_5);
            break;
        }
        case 33:{
            targetingBind(Keybinds::TARGET_ARENA_1);
            break;
        }
        case 34:{
            targetingBind(Keybinds::TARGET_ARENA_2);
            break;
        }
        case 35:{
            targetingBind(Keybinds::TARGET_ARENA_3);
            break;
        }
        case 36:{
            targetingBind(Keybinds::TARGET_ARENA_4);
            break;
        }
        case 37:{
            targetingBind(Keybinds::TARGET_ARENA_5);
            break;
        }
        case 38:{   //camera keybinds 38 39 40
            cameraBind(Keybinds::CAMERA_ZOOM_IN);
            break;
        }
        case 39:{
            cameraBind(Keybinds::CAMERA_ZOOM_IN);
            break;
        }
        case 40:{
            cameraBind(Keybinds::CAMERA_REVERSE);
            break;
        }
        case 41:{
            actionBar[0]->callSlotSpell(0);
            break;
        }
        case 42:{
            actionBar[0]->callSlotSpell(1);
            break;
        }
        case 43:{
            actionBar[0]->callSlotSpell(2);
            break;
        }
        case 44:{
            actionBar[0]->callSlotSpell(3);
            break;
        }
        case 45:{
            actionBar[0]->callSlotSpell(4);
            break;
        }
        case 46:{
            actionBar[0]->callSlotSpell(5);
            break;
        }
        case 47:{
            actionBar[0]->callSlotSpell(6);
            break;
        }
        case 48:{
            actionBar[0]->callSlotSpell(7);
            break;
        }
        case 49:{
            actionBar[0]->callSlotSpell(8);
            break;
        }
        case 50:{
            actionBar[0]->callSlotSpell(9);
            break;
        }
        case 51:{ //start bar 2
            actionBar[1]->callSlotSpell(0);
            break;
        }
        case 52:{
            actionBar[1]->callSlotSpell(1);
            break;
        }
        case 53:{
            actionBar[1]->callSlotSpell(2);
            break;
        }
        case 54:{
            actionBar[1]->callSlotSpell(3);
            break;
        }
        case 55:{
            actionBar[1]->callSlotSpell(4);
            break;
        }
        case 56:{
            actionBar[1]->callSlotSpell(5);
            break;
        }
        case 57:{
            actionBar[1]->callSlotSpell(6);
            break;
        }
        case 58:{
            actionBar[1]->callSlotSpell(7);
            break;
        }
        case 59:{
            actionBar[1]->callSlotSpell(8);
            break;
        }
        case 60:{
            actionBar[1]->callSlotSpell(9);
            break;
        }
        case 61:{ //interface 0
            togglePane(Keybinds::SPELLBOOK);
            break;
        }
        case 62:{
            togglePane(Keybinds::CLAN);
            break;
        }
        case 63:{
            togglePane(Keybinds::HONOR);
            break;
        }
        case 64:{
            togglePane(Keybinds::MAINMENU);
            break;
        }
        case 65:{
            togglePane(Keybinds::CHARACTER);
            break;
        }
        case 66:{
            togglePane(Keybinds::MACRO);
            break;
        }
        case 67:{
            togglePane(Keybinds::SOCIAL);
            break;
        }
        case 68:{ //interface 7
            togglePane(Keybinds::MAP);
            break;
        }
        case 69:{
            toggleChat();
            break;
        }
        case 70:{//Reply Whisper
            whisper(Keybinds::REPLY_WHISPER);
            break;
        }
        case 71:{//Re-Whisper
            whisper(Keybinds::RE_WHISPER);
            break;
        }
        case 72:{
            screenshot();//Take Screenshot
            break;
        }

        }
}

void MainWindow::initDefaultKeybinds(){
    int i = 0;
    //0
    shortcut[i]->setKey(QKeySequence(tr("W"))); // Move Forward
    i++;
    shortcut[i]->setKey(QKeySequence(tr("S"))); // Move Backward
    i++;
    shortcut[i]->setKey(QKeySequence(tr("A"))); // Turn Left
    i++;
    shortcut[i]->setKey(QKeySequence(tr("D"))); // Turn Right
    i++;
    shortcut[i]->setKey(QKeySequence()); // Move Left
    i++;
    shortcut[i]->setKey(QKeySequence()); // Move Right
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Space"))); //Jump
    i++;
    shortcut[i]->setKey(QKeySequence(tr(""))); //Toggle Attack
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Tab"))); // Target Nearest Enemy
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+Tab"))); // Target Previous Enemy
    i++;
    //10
    shortcut[i]->setKey(QKeySequence()); //Target Nearest Enemy Player
    i++;
    shortcut[i]->setKey(QKeySequence()); //Target Previous Enemy Player
    i++;
    shortcut[i]->setKey(QKeySequence()); //Target Nearest Friendly Player
    i++;
    shortcut[i]->setKey(QKeySequence()); //Target Previous Friendly Player
    i++;
    shortcut[i]->setKey(QKeySequence(tr("F1"))); //Target Self
    i++;
    shortcut[i]->setKey(QKeySequence(tr("F2"))); //Target Party Member 1
    i++;
    shortcut[i]->setKey(QKeySequence(tr("F3"))); //Target Party Member 2
    i++;
    shortcut[i]->setKey(QKeySequence(tr("F4"))); //Target Party Member 3
    i++;
    shortcut[i]->setKey(QKeySequence(tr("F5"))); //Target Party Member 4
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+F1"))); //Target Pet
    i++;
    //20
    shortcut[i]->setKey(QKeySequence(tr("Shift+F2"))); //Target Party Pet 1
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+F3"))); //Target Party Pet 2
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+F4"))); //Target Party Pet 3
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+F5"))); //Target Party Pet 4
    i++;
    shortcut[i]->setKey(QKeySequence()); //Assist Target
    i++;
    shortcut[i]->setKey(QKeySequence()); //Toggle Nameplates
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+V"))); //Toggle Friendly Nameplates
    i++;
    shortcut[i]->setKey(QKeySequence(tr("V"))); //Set Focus
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Ctrl+A"))); //Focus Arena 1
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Ctrl+S"))); //Focus Arena 2
    i++;
    //30
    shortcut[i]->setKey(QKeySequence(tr("Ctrl+D"))); //Focus Arena 3
    i++;
    shortcut[i]->setKey(QKeySequence()); //Focus Arena 4
    i++;
    shortcut[i]->setKey(QKeySequence()); //Focus Arena 5
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+1"))); //Target Arena 1
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+2"))); //Target Arena 2
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Shift+3"))); //Target Arena 3
    i++;
    shortcut[i]->setKey(QKeySequence()); //Target Arena 4
    i++;
    shortcut[i]->setKey(QKeySequence()); //Target Arena 5
    i++;
    shortcut[i]->setKey(QKeySequence()); //Camera Zoom In
    i++;
    shortcut[i]->setKey(QKeySequence()); //Camera Zoom Out
    i++;
    //40
    shortcut[i]->setKey(QKeySequence()); //Camera Reverse
    i++;
    shortcut[i]->setKey(QKeySequence(tr("1"))); //Primary Button 0
    i++;
    shortcut[i]->setKey(QKeySequence(tr("2"))); //Primary Button 1
    i++;
    shortcut[i]->setKey(QKeySequence(tr("3"))); //Primary Button 2
    i++;
    shortcut[i]->setKey(QKeySequence(tr("4"))); //Primary Button 3
    i++;
    shortcut[i]->setKey(QKeySequence(tr("5"))); //Primary Button 4
    i++;
    shortcut[i]->setKey(QKeySequence(tr("6"))); //Primary Button 5
    i++;
    shortcut[i]->setKey(QKeySequence(tr("7"))); //Primary Button 6
    i++;
    shortcut[i]->setKey(QKeySequence(tr("8"))); //Primary Button 7
    i++;
    shortcut[i]->setKey(QKeySequence(tr("9"))); //Primary Button 8
    i++;
    //50
    shortcut[i]->setKey(QKeySequence(tr("0"))); //Primary Button 9
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 0
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 1
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 2
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 3
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 4
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 5
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 6
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 7
    i++;
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 8
    i++;
    //60
    shortcut[i]->setKey(QKeySequence()); //Secondary Button 9
    i++;
    shortcut[i]->setKey(QKeySequence(tr("P"))); //Toggle Spellbook
    i++;
    shortcut[i]->setKey(QKeySequence(tr("G"))); //Toggle Clan
    i++;
    shortcut[i]->setKey(QKeySequence(tr("H"))); //Toggle Honor
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Escape"))); //Open Main Menu
    i++;
    shortcut[i]->setKey(QKeySequence(tr("C"))); //Toggle Char Menu
    i++;
    shortcut[i]->setKey(QKeySequence()); //Toggle Macro Menu
    i++;
    shortcut[i]->setKey(QKeySequence(tr("O"))); //Toggle Social
    i++;
    shortcut[i]->setKey(QKeySequence(tr("M"))); //Toggle Map
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Return"))); //Open Chat
    i++;
    //70
    shortcut[i]->setKey(QKeySequence(tr("R"))); //Reply Whisper
    i++;
    shortcut[i]->setKey(QKeySequence()); //Re-Whisper
    i++;
    shortcut[i]->setKey(QKeySequence()); //Take Screenshot

    for(i = 0; i<73; i++){
        keybindString[i] = shortcut[i]->key().toString();
    }

    saveKeybinds();
    emit pushKeybinds(keybindString);
}


void MainWindow::saveKeybinds(){
    qDebug() << "Saving Keybinds to File";
    QString path = QCoreApplication::applicationDirPath() + "/userdata/keybinds.txt";
    QDir dir;
    if(dir.mkdir(QCoreApplication::applicationDirPath()+"/userdata")){
        qDebug() << "Doesnt Exist Creating Userdata Folder";
    }
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)){
          qDebug() << file.errorString();
          return;
    }

    QDataStream out(&file);
    for (int i = 0; i < KEYBINDCOUNT; i++){
        //qDebug() << "Saving shortcut" << i << shortcut[i]->key().toString();
        out << shortcut[i]->key().toString();
    }

    file.close();
}

void MainWindow::initKeybinds(){
    QString path = QCoreApplication::applicationDirPath() + "/userdata/keybinds.txt";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
          qDebug() << file.errorString();
          initDefaultKeybinds();
          return;
    }

    QString tempShortcut[KEYBINDCOUNT];
    QDataStream in(&file);
    QString readShortcut;
    int i = 0;

    for (i = 0; i < KEYBINDCOUNT; i++){
        if(in.atEnd() && i != KEYBINDCOUNT-1){
            //use default values
            qDebug() << i << KEYBINDCOUNT;
            qDebug() << "Invalid file initializing defaults";
            file.close();
            initDefaultKeybinds();
            return;
        }
        in >> readShortcut;//handle shortcut after
        //qDebug() << "Read:" << i << readShortcut;
        tempShortcut[i] = readShortcut;
    }

    for (i = 0; i < KEYBINDCOUNT; i++){
        shortcut[i]->setKey(tempShortcut[i]);
        keybindString[i] = shortcut[i]->key().toString();
    }
    emit pushKeybinds(keybindString);
    file.close();
}

void MainWindow::saveActionBars(){
    qDebug() << "Saving Action Bars to File";
    QString path = QCoreApplication::applicationDirPath() + "/userdata/actionbars.txt";
    QDir dir;
    if(dir.mkdir(QCoreApplication::applicationDirPath()+"/userdata")){
        qDebug() << "Doesnt Exist Creating Userdata Folder";
    }
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)){
          qDebug() << file.errorString();
          return;
    }

    QDataStream out(&file);
    quint32 spellId;
    int i;
    for(i = 1; i < 11; i++){
        spellId = (quint32)actionBar[0]->getButtonSpell(i);
        out << spellId;
        spellId = (quint32)actionBar[1]->getButtonSpell(i);
        out << spellId;
    }

    file.close();
}

void MainWindow::loadActionBars(){
    qDebug() << "Loading Action Bars";
    QString path = QCoreApplication::applicationDirPath() + "/userdata/actionbars.txt";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
          qDebug() << file.errorString();
          initDefaultActionbars();
          return;
    }

    QDataStream in(&file);
    quint32 spellId;
    int i =0;
    for(i = 1; i < 11; i++){
        in >> spellId;
        if (spellId > 1300){
            qDebug() << "Bad File... Initializing Defaults";
            initDefaultActionbars();
            return;
        }
        actionBar[0]->setButtonSpell((uint32_t)spellId,i);
        in >> spellId;
        if (spellId > 1300){
            qDebug() << "Bad File... Initializing Defaults";
            initDefaultActionbars();
            return;
        }
        actionBar[1]->setButtonSpell((uint32_t)spellId,i);
    }

    file.close();
}

 void MainWindow::initDefaultActionbars(){ //change this later lol
     for(int i = 1; i < 11; i++){
         actionBar[0]->setButtonSpell(qrand()%4,i);
         actionBar[1]->setButtonSpell(qrand()%4,i);
     }
     saveActionBars();
}

void MainWindow::update(){

}

MainWindow::~MainWindow()
{
    saveKeybinds();
    saveActionBars();
    for(int i = 0; i<KEYBINDCOUNT; i++){
        delete shortcut[i];
    }
    delete keybindMapper;
    delete loginScreen;
    delete ui;
}

void MainWindow::openOption(QString name){
    if(name == "Help"){
        gameMenu->setVisible(false);
    }
    else if (name == "Options"){
        gameMenu->setVisible(false);
        optionsMenu->show();
    }
    else if (name == "Macros"){
        gameMenu->setVisible(false);
    }
    else if (name == "Logout"){
        gameMenu->setVisible(false);
    }
    else if (name == "Exit Game"){
        gameMenu->setVisible(false);
    }
    else{
        qDebug() << "Error Invalid Input";
        return;
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
    if (event->oldSize().height() == -1 || event->oldSize().width() == -1){
        return;
    }

    double scale_factor_x = 550.0 / 1200.0;
    double scale_factor_y = 350.0 / 900.0;

    gameMenu->move(event->size().width()*scale_factor_x,
                  event->size().height()*scale_factor_y);


    if(event->size().width()>900){
        scale_factor_x = 500.0 / 1200.0;
        scale_factor_y = 200.0 / 900.0;

        honorFrame->move(event->size().width()*scale_factor_x,
                         event->size().height()*scale_factor_y);


        scale_factor_x = 200.0 / 1200.0;
        scale_factor_y = 200.0 / 900.0;

        guildFrame->move(event->size().width()*scale_factor_x,
                         event->size().height()*scale_factor_y);


        scale_factor_x = 800.0 / 1200.0;
        scale_factor_y = 200.0 / 900.0;

        spellBook->move(event->size().width()*scale_factor_x,
                        event->size().height()*scale_factor_y);
    }
    scale_factor_x = 12.5 / 1200.0;
    scale_factor_y = 12.5 / 900.0;

    playerFrame->move(event->size().width()*scale_factor_x,
                      event->size().height()*scale_factor_y);

    scale_factor_x = (double)287.5 / (double) 1200;

    targetFrame->move(event->size().width()*scale_factor_x,
                      event->size().height()*scale_factor_y);


    scale_factor_x = (double)12.5 / (double) 1200;
    scale_factor_y = (double)137.5 / (double) 900;

    partyFrame->move(event->size().width()*scale_factor_x,
                     event->size().height()*scale_factor_y);

    scale_factor_x = (double)767.5 / (double) 1200;
    scale_factor_y = (double)12.5 / (double) 900;

    playerBuff->move(event->size().width()*scale_factor_x,
                   event->size().height()*scale_factor_y);


    scale_factor_y = (double)56.5 / (double) 900;

    playerDebuff->move(event->size().width()*scale_factor_x,
                     event->size().height()*scale_factor_y);

    scale_factor_x = (double)287.5 / (double) 1200;
    scale_factor_y = (double)117.5 / (double) 900;

    targetBuff->move(event->size().width()*scale_factor_x,
                     event->size().height()*scale_factor_y);


    scale_factor_y = (double)143.5 / (double) 900;

    targetDebuff->move(event->size().width()*scale_factor_x,
                       event->size().height()*scale_factor_y);

    scale_factor_x = (double)(600 - 527/2) / (double) 1200;
    scale_factor_y = (double)(450 - 452/2) / (double) 900;

    optionsMenu->move(event->size().width()*scale_factor_x,
                      event->size().height()*scale_factor_y);


    //qDebug() << "Window Resized From" << event->oldSize() << " to " << event->size();
    ui->gameScreen->resize(event->size());
    //resize openglwidget too ? need to resize other stuff inside this when init'd
    ui->openGLWidget->resize(event->size());

    emit newSize(event->size());
}


void MainWindow::castSpell(int buttonPos){
    printf("Casting from Slot %i\n", buttonPos);
    fflush(stdout);
    //figure out current data of button
    //check for CD / target
    //handle it
}

//void MainWindow::keyPressEvent(QKeyEvent *event){

//}


