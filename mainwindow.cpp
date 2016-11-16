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
    actionBar[1] = new ActionBar(ui->gameScreen);
    actionBar[0]->move(350,800);
    actionBar[1]->move(350,850);

    //test stuff for action bars -- remove later
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
    guildFrame = new GuildFrame(ui->gameScreen);

    //honor menu
    honorFrame = new HonorFrame(ui->gameScreen);

    //game menu
    gameMenu = new GameMenu(ui->gameScreen);

    //game menu options popups
    mainMenu = new OptionsFrame(ui->gameScreen);

    //game menu keybind popup
    //KeybindMenu *keybindMenu = new KeybindMenu(ui->gameScreen);


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
    connect(gameMenu,SIGNAL(openThis(QString)),this,SLOT(test(QString)));
    connect(this,SIGNAL(newSize(QSize)),partyFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),guildFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),honorFrame,SLOT(resizeMe(QSize)));
    connect(this,SIGNAL(newSize(QSize)),gameMenu,SLOT(resizeMe(QSize)));

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


    //our "constantly calling update function stuff"
    connect(loginButton,SIGNAL(clicked(bool)),this,SLOT(login()));
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
    initDefaultKeybinds();
    connect(this,SIGNAL(pushKeybinds(QString*)),mainMenu,SLOT(updateKeybinds(QString*)));

    QString *pushKeybindStrings = keybindString;
    emit pushKeybinds(pushKeybindStrings);

    connect(mainMenu,SIGNAL(disableShortcutsSend()),this,SLOT(disableShortcuts()));
    connect(mainMenu,SIGNAL(enableShortcutsSend()),this,SLOT(enableShortcuts()));


//    qDebug() << shortcut[0]->key().toString();
//    qDebug() << shortcut[9]->key().toString();
//    qDebug() << shortcut[10]->key().toString();

//    qDebug() << "Shortcut Testing...";
    //shortcut testing stuff

//      QKeySequence testx = QKeySequence("Space");
//   QKeySequence testy = QKeySequence("Alt+R");
//      shortcut[0]->setKey(testx);
//    shortcut[1]->setKey(testy);
//      connect(shortcut[0],SIGNAL(activated()),keybindMapper,SLOT(map()));
//      keybindMapper->setMapping(shortcut[0],0);

//    connect(shortcut[1],SIGNAL(activated()),keybindMapper,SLOT(map()));
//    keybindMapper->setMapping(shortcut[1],1);


//    functPointer fp;
//    fp = &MainWindow::showHonor;
//    mainkeyBinds[test] = fp;
//    qDebug() << "Shortcut Testing2...";

//    //test save keybinds to file
//    QFile file("C:/Users/Danny/Desktop/Github Repos/GUI/keybinds/keybinds.txt");
//    if (!file.open(QIODevice::WriteOnly)){
//          qDebug() << file.errorString();
//          return;
//    }

    //do stuff here
//    QDataStream out(&file);
//    QString a = "1", b = "2" , c = "3";
//    out << a << b << c;
//    file.close();
//    qDebug() << "Shortcut Testing3...";

//    //test reading keybinds from file
//    if (!file.open(QIODevice::ReadOnly)){
//          qDebug() << file.errorString();
//          return;
//    }

//    //do stuff here
//    QDataStream in(&file);
//    QString name2;
//    QKeySequence test2;
//    in >> name2 >> test2;

//    qDebug() << "Shortcut Testing3.5...";
//    file.close();

//    qDebug() << name2 << test2;
//    shortcut[0]->setKey(test2);
//    shortcut[0].setObjectName

//    qDebug() << "Shortcut Testing4...";

    //END SHORTCUT TESTING STUFF
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
            if (mainMenu->isVisible()){
                mainMenu->setVisible(false);
                break;
            }
            gameMenu->isVisible()? gameMenu->setVisible(false):gameMenu->show();
            break;
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

void MainWindow::movePlayer(int direction){
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
            movePlayer(FORWARD);
            break;
        }
        case 1:{
            movePlayer(BACKWARD);
             break;
        }
        case 2:{
            movePlayer(TURN_LEFT);
            break;
        }
        case 3:{
            movePlayer(TURN_RIGHT);
            break;
        }
        case 4:{
            movePlayer(MOVE_LEFT);
            break;
        }
        case 5:{
            movePlayer(MOVE_RIGHT);
            break;
        }
        case 6:{

            break;
        }
        case 7:{

            break;
        }
        case 8:{
            movePlayer(JUMP);
            break;
        }
        case 9:{

            break;
        }
        case 10:{

            break;
        }
        case 11:{

            break;
        }
        case 12:{

            break;
        }
        case 13:{

            break;
        }
        case 14:{

            break;
        }
        case 15:{

            break;
        }
        case 16:{

            break;
        }
        case 17:{

            break;
        }
        case 18:{

            break;
        }
        case 19:{

            break;
        }
        case 20:{

            break;
        }
        case 21:{

            break;
        }
        case 22:{

            break;
        }
        case 23:{

            break;
        }
        case 24:{

            break;
        }
        case 25:{

            break;
        }
        case 26:{

            break;
        }
        case 27:{

            break;
        }
        case 28:{

            break;
        }
        case 29:{

            break;
        }
        case 30:{

            break;
        }
        case 31:{

            break;
        }
        case 32:{

            break;
        }
        case 33:{

            break;
        }
        case 34:{

            break;
        }
        case 35:{

            break;
        }
        case 36:{

            break;
        }
        case 37:{

            break;
        }
        case 38:{

            break;
        }
        case 39:{

            break;
        }
        case 40:{

            break;
        }
        case 41:{

            break;
        }
        case 42:{

            break;
        }
        case 43:{

            break;
        }
        case 44:{

            break;
        }
        case 45:{

            break;
        }
        case 46:{

            break;
        }
        case 47:{

            break;
        }
        case 48:{

            break;
        }
        case 49:{

            break;
        }
        case 50:{

            break;
        }
        case 51:{

            break;
        }
        case 52:{

            break;
        }
        case 53:{

            break;
        }
        case 54:{

            break;
        }
        case 55:{

            break;
        }
        case 56:{

            break;
        }
        case 57:{

            break;
        }
        case 58:{

            break;
        }
        case 59:{

            break;
        }
        case 60:{

            break;
        }
        case 61:{
            togglePane(SPELLBOOK);
            break;
        }
        case 62:{
            togglePane(CLAN);
            break;
        }
        case 63:{
            togglePane(HONOR);
            break;
        }
        case 64:{
            togglePane(MAINMENU);
            break;
        }
        case 65:{
            togglePane(CHARACTER);
            break;
        }
        case 66:{
            togglePane(MACRO);
            break;
        }
        case 67:{
            togglePane(SOCIAL);
            break;
        }
        case 68:{
            togglePane(MAP);
            break;
        }
        case 69:{
            //OPEN CHAT
            break;
        }
        case 70:{
            //Reply Whisper
            break;
        }
        case 71:{
            //Re-Whisper
            break;
        }
        case 72:{
            //Take Screenshot
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
    shortcut[i]->setKey(QKeySequence(tr("10"))); //Primary Button 9
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
    shortcut[i]->setKey(QKeySequence()); //Toggle Clan
    i++;
    shortcut[i]->setKey(QKeySequence(tr("H"))); //Toggle Honor
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Escape"))); //Open Main Menu
    i++;
    shortcut[i]->setKey(QKeySequence()); //Toggle Char Menu
    i++;
    shortcut[i]->setKey(QKeySequence()); //Toggle Macro Menu
    i++;
    shortcut[i]->setKey(QKeySequence(tr("O"))); //Toggle Social
    i++;
    shortcut[i]->setKey(QKeySequence(tr("M"))); //Toggle Map
    i++;
    shortcut[i]->setKey(QKeySequence(tr("Enter"))); //Open Chat
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

}

void MainWindow::updateKeybinds(){

}

void MainWindow::initKeybinds(){
    QFile file("C:/Users/Danny/Desktop/Github Repos/GUI/keybinds.txt");
    if (!file.open(QIODevice::ReadOnly)){
          qDebug() << file.errorString();
          return;
    }

    QDataStream in(&file);
    for (int i = 0; i < KEYBINDCOUNT; i++){
        QKeySequence readShortcut;
        if(in.atEnd()){
            //use default values
            initDefaultKeybinds();
            break;
        }
        in >> readShortcut;//handle shortcut after
        shortcut[i]->setKey(readShortcut);
    }

    file.close();
}

void MainWindow::saveKeybinds(){
    QFile file("C:/Users/Danny/Desktop/Github Repos/GUI/keybinds.txt");
    if (!file.open(QIODevice::WriteOnly)){
          qDebug() << file.errorString();
          return;
    }

    QDataStream out(&file);
    for (int i = 0; i < KEYBINDCOUNT; i++){
        out << shortcut[i]->key();
    }

    file.close();
}


void MainWindow::update(){

}

void MainWindow::test2(){
    qDebug() << "Test2";
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

    scale_factor_x = 550.0 / 1200.0;
    scale_factor_y = 350.0 / 900.0;

    gameMenu->move(event->size().width()*scale_factor_x,
                  event->size().height()*scale_factor_y);


    scale_factor_x = 500.0 / 1200.0;
    scale_factor_y = 200.0 / 900.0;

    honorFrame->move(event->size().width()*scale_factor_x,
                     event->size().height()*scale_factor_y);


    scale_factor_x = 200.0 / 1200.0;
    scale_factor_y = 200.0 / 900.0;

    guildFrame->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);

    scale_factor_x = 950.0 / 1200.0;
    scale_factor_y = 800.0 / 900.0;

    menuBar->move(event->size().width()*scale_factor_x,
                                                    event->size().height()*scale_factor_y);


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


    scale_factor_y = (double)144.5 / (double) 900;

    targetDebuff->move(event->size().width()*scale_factor_x,
                       event->size().height()*scale_factor_y);

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


