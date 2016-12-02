#include "keybindmenu.hpp"

//blah

const QString moveKeybindDescName[7] = {"Move Forward",
                                  "Move Backward",
                                  "Turn Left",
                                  "Turn Right",
                                  "Move Left",
                                  "Move Right",
                                  "Jump"},
        combatKeybindDescName = "Toggle Attack",
        targetingKeybindDescName[30] = {"Target Nearest Enemy","Target Previous Enemy",
                                        "Target Nearest Enemy Player","Target Previous Enemy Player",
                                        "Target Nearest Friendly Player","Target Previous Friendly Player",
                                        "Target Self","Target Party Member 1","Target Party Member 2","Target Party Member 3","Target Party Member 4",
                                        "Target Pet","Target Party Pet 1","Target Party Pet 2","Target Party Pet 3","Target Party Pet 4",
                                        "Assist Target","Toggle Nameplates","Toggle Friendly Nameplates","Set Focus",
                                        "Focus Arena 1","Focus Arena 2","Focus Arena 3","Focus Arena 4","Focus Arena 5",
                                        "Target Arena 1","Target Arena 2","Target Arena 3","Target Arena 4","Target Arena 5"},
        cameraKeybindDescName[3] = {"Camera Zoom In","Camera Zoom Out","Camera Reverse"},
        actionPrimaryButtonKeybindDescName[10] = {"Main Button 0","Main Button 1","Main Button 2","Main Button 3","Main Button 4",
                                           "Main Button 5","Main Button 6","Main Button 7","Main Button 8","Main Button 9"},
        actionSecondaryButtonKeybindDescName[10] = {"Secondary Button 0","Secondary Button 1","Secondary Button 2","Secondary Button 3","Secondary Button 4",
                                           "Secondary Button 5","Secondary Button 6","Secondary Button 7","Secondary Button 8","Secondary Button 9"},
        interfaceKeybindDescName[8] = {"Toggle Spellbook","Toggle Clan","Toggle Honor","Open Main Menu",
                                       "Toggle Char Menu","Toggle Macro","Toggle Social","Toggle Map"},
        chatKeybindDescName[3] = {"Open Chat","Reply Whisper","Re-Whisper"},
        miscKeybindDescName = "Take Screenshot";


KeybindMenu::KeybindMenu(QWidget *parent)
    : QFrame(parent)
{
    setObjectName("keybindMenu");
    resize(450,450);
    move(600 - this->width()/2, 450 - this->height()/2);
    setStyleSheet("#keybindMenu{"
                  "border: 2px solid black;"
                  "border-left: none}");


    scrollArea = new QScrollArea(this);

    mainFrame = new QFrame(this);
    mainFrame->setGeometry(0,0,415,2000);
    mainFrame->setMinimumWidth(250);

    gridLayout = new QGridLayout(mainFrame);
    gridLayout->setMargin(10);
    gridLayout->setSpacing(10);

    gridLayout->setColumnMinimumWidth(0,150);
    gridLayout->setColumnMinimumWidth(1,50);
    gridLayout->setColumnMinimumWidth(2,50);
    gridLayout->setColumnStretch(0,2);
    gridLayout->setColumnStretch(1,1);
    gridLayout->setColumnStretch(2,1);
    gridLayout->setRowMinimumHeight(0,25);
    gridLayout->setRowMinimumHeight(1,25);
    gridLayout->setRowMinimumHeight(2,25);

    QString objectName;
    //init signal mappers
    keybindMapperMain = new QSignalMapper(this);
    connect(keybindMapperMain,SIGNAL(mapped(int)),this,SLOT(setBindMain(int)));
    keybindMapperBackup = new QSignalMapper(this);
    connect(keybindMapperBackup,SIGNAL(mapped(int)),this,SLOT(setBindBackup(int)));

    //indexes for grid
    int i = 0, index = 0, sectionIndex = 0, buttonNum = 0;

    //column header labels
    for(i = 0; i<3; i++){
        header[i] = new QLabel(this);
        header[i]->setAlignment(Qt::AlignCenter);
        header[i]->setStyleSheet("font-size: 12px;"
                                 "font-weight: bold;");
    }
    header[0]->setText("Action");
    header[0]->setFixedHeight(25);
    header[1]->setText("Key 1");
    header[1]->setFixedHeight(25);
    header[2]->setText("Key 2");
    header[2]->setFixedHeight(25);
    gridLayout->addWidget(header[0],index,0);
    gridLayout->addWidget(header[1],index,1);
    gridLayout->addWidget(header[2],index,2);
    index++;

    //move section labels
    sectionHeader[sectionIndex] = new QLabel(this);
    sectionHeader[sectionIndex]->setAlignment(Qt::AlignCenter);
    sectionHeader[sectionIndex]->setText("Movement Options");
    sectionHeader[sectionIndex]->setStyleSheet("font-weight: bold;");
    sectionHeader[sectionIndex]->setFixedHeight(25);
    gridLayout->addWidget(sectionHeader[sectionIndex],index,0);
    index++;
    sectionIndex++;

    for (i = 0; i<MOVE_BINDS; i++){
        keybindDesc[buttonNum] = new QLabel(this);
        keybindDesc[buttonNum]->setText(moveKeybindDescName[i]);
        keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
        keybindDesc[buttonNum]->setFixedHeight(25);

        keybind[buttonNum] = new QPushButton(this);
        keybind[buttonNum]->setFixedHeight(25);
        keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("moveKeybind%1").arg(i);
        keybind[buttonNum]->setObjectName(objectName);
        connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

        keybindBackup[buttonNum] = new QPushButton(this);
        keybindBackup[buttonNum]->setFixedHeight(25);
        keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("moveKeybindBackup%1").arg(i);
        keybindBackup[buttonNum]->setObjectName(objectName);
        connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperBackup,SLOT(map()));
        keybindMapperBackup->setMapping(keybindBackup[buttonNum],buttonNum);

        gridLayout->addWidget(keybindDesc[buttonNum],index,0);
        gridLayout->addWidget(keybind[buttonNum],index,1);
        gridLayout->addWidget(keybindBackup[buttonNum],index,2);
        index++;
        buttonNum++;
    }

    //misc section labels
    sectionHeader[sectionIndex] = new QLabel(this);
    sectionHeader[sectionIndex]->setAlignment(Qt::AlignCenter);
    sectionHeader[sectionIndex]->setText("Combat Options");
    sectionHeader[sectionIndex]->setStyleSheet("font-weight: bold;");
    sectionHeader[sectionIndex]->setFixedHeight(25);
    gridLayout->addWidget(sectionHeader[sectionIndex],index,0);
    index++;
    sectionIndex++;

    keybindDesc[buttonNum] = new QLabel(this);
    keybindDesc[buttonNum]->setText(combatKeybindDescName);
    keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
    keybindDesc[buttonNum]->setFixedHeight(25);

    keybind[buttonNum] = new QPushButton(this);
    keybind[buttonNum]->setFixedHeight(25);
    keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
    objectName = QString("combatKeybind%1").arg(i);
    keybind[buttonNum]->setObjectName(objectName);
    connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
    keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

    keybindBackup[buttonNum] = new QPushButton(this);
    keybindBackup[buttonNum]->setFixedHeight(25);
    keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
    objectName = QString("combatKeybindBackup%1").arg(i);
    keybindBackup[buttonNum]->setObjectName(objectName);
    connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperBackup,SLOT(map()));
    keybindMapperBackup->setMapping(keybindBackup[buttonNum],buttonNum);


    gridLayout->addWidget(keybindDesc[buttonNum],index,0);
    gridLayout->addWidget(keybind[buttonNum],index,1);
    gridLayout->addWidget(keybindBackup[buttonNum],index,2);
    index++;
    buttonNum++;


    //targeting section labels
    sectionHeader[sectionIndex] = new QLabel(this);
    sectionHeader[sectionIndex]->setAlignment(Qt::AlignCenter);
    sectionHeader[sectionIndex]->setText("Targeting Options");
    sectionHeader[sectionIndex]->setStyleSheet("font-weight: bold;");
    sectionHeader[sectionIndex]->setFixedHeight(25);
    gridLayout->addWidget(sectionHeader[sectionIndex],index,0);
    index++;
    sectionIndex++;

    for (i = 0; i<TARGET_BINDS; i++){
        keybindDesc[buttonNum] = new QLabel(this);
        keybindDesc[buttonNum]->setText(targetingKeybindDescName[i]);
        keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
        keybindDesc[buttonNum]->setFixedHeight(25);

        keybind[buttonNum] = new QPushButton(this);
        keybind[buttonNum]->setFixedHeight(25);
        keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("targetingKeybind%1").arg(i);
        keybind[buttonNum]->setObjectName(objectName);
        connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

        keybindBackup[buttonNum] = new QPushButton(this);
        keybindBackup[buttonNum]->setFixedHeight(25);
        keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("targetingKeybindBackup%1").arg(i);
        keybindBackup[buttonNum]->setObjectName(objectName);
        connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybindBackup[buttonNum],buttonNum);

        gridLayout->addWidget(keybindDesc[buttonNum],index,0);
        gridLayout->addWidget(keybind[buttonNum],index,1);
        gridLayout->addWidget(keybindBackup[buttonNum],index,2);
        index++;
        buttonNum++;
    }

    //camera section labels
    sectionHeader[sectionIndex] = new QLabel(this);
    sectionHeader[sectionIndex]->setAlignment(Qt::AlignCenter);
    sectionHeader[sectionIndex]->setText("Camera Options");
    sectionHeader[sectionIndex]->setStyleSheet("font-weight: bold;");
    sectionHeader[sectionIndex]->setFixedHeight(25);
    gridLayout->addWidget(sectionHeader[sectionIndex],index,0);
    index++;
    sectionIndex++;

    for (i = 0; i<CAMERA_BINDS; i++){
        keybindDesc[buttonNum] = new QLabel(this);
        keybindDesc[buttonNum]->setText(cameraKeybindDescName[i]);
        keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
        keybindDesc[buttonNum]->setFixedHeight(25);

        keybind[buttonNum] = new QPushButton(this);
        keybind[buttonNum]->setFixedHeight(25);
        keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("cameraKeybind%1").arg(i);
        keybind[buttonNum]->setObjectName(objectName);
        connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

        keybindBackup[buttonNum] = new QPushButton(this);
        keybindBackup[buttonNum]->setFixedHeight(25);
        keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("cameraKeybindBackup%1").arg(i);
        keybindBackup[buttonNum]->setObjectName(objectName);
        connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybindBackup[buttonNum],buttonNum);

        gridLayout->addWidget(keybindDesc[buttonNum],index,0);
        gridLayout->addWidget(keybind[buttonNum],index,1);
        gridLayout->addWidget(keybindBackup[buttonNum],index,2);
        index++;
        buttonNum++;
    }

    //action button section labels
    sectionHeader[sectionIndex] = new QLabel(this);
    sectionHeader[sectionIndex]->setAlignment(Qt::AlignCenter);
    sectionHeader[sectionIndex]->setText("Action Button Options");
    sectionHeader[sectionIndex]->setStyleSheet("font-weight: bold;");
    sectionHeader[sectionIndex]->setFixedHeight(25);
    gridLayout->addWidget(sectionHeader[sectionIndex],index,0);
    index++;
    sectionIndex++;

    for (i = 0; i<ACTION_PRIMARY_BINDS; i++){
        keybindDesc[buttonNum] = new QLabel(this);
        keybindDesc[buttonNum]->setText(actionPrimaryButtonKeybindDescName[i]);
        keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
        keybindDesc[buttonNum]->setFixedHeight(25);

        keybind[buttonNum] = new QPushButton(this);
        keybind[buttonNum]->setFixedHeight(25);
        keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("actionPrimaryButtonKeybind%1").arg(i);
        keybind[buttonNum]->setObjectName(objectName);
        connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

        keybindBackup[buttonNum] = new QPushButton(this);
        keybindBackup[buttonNum]->setFixedHeight(25);
        keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("actionPrimaryButtonKeybindBackup%1").arg(i);
        keybindBackup[buttonNum]->setObjectName(objectName);
        connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybindBackup[buttonNum],buttonNum);

        gridLayout->addWidget(keybindDesc[buttonNum],index,0);
        gridLayout->addWidget(keybind[buttonNum],index,1);
        gridLayout->addWidget(keybindBackup[buttonNum],index,2);
        index++;
        buttonNum++;
    }

    for (i = 0; i<ACTION_SECONDARY_BINDS; i++){
        keybindDesc[buttonNum] = new QLabel(this);
        keybindDesc[buttonNum]->setText(actionSecondaryButtonKeybindDescName[i]);
        keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
        keybindDesc[buttonNum]->setFixedHeight(25);

        keybind[buttonNum] = new QPushButton(this);
        keybind[buttonNum]->setFixedHeight(25);
        keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("actionSecondaryButtonKeybind%1").arg(i);
        keybind[buttonNum]->setObjectName(objectName);
        connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

        keybindBackup[buttonNum] = new QPushButton(this);
        keybindBackup[buttonNum]->setFixedHeight(25);
        keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("actionSecondaryButtonKeybindBackup%1").arg(i);
        keybindBackup[buttonNum]->setObjectName(objectName);
        connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybindBackup[buttonNum],buttonNum);

        gridLayout->addWidget(keybindDesc[buttonNum],index,0);
        gridLayout->addWidget(keybind[buttonNum],index,1);
        gridLayout->addWidget(keybindBackup[buttonNum],index,2);
        index++;
        buttonNum++;
    }

    //interface section labels
    sectionHeader[sectionIndex] = new QLabel(this);
    sectionHeader[sectionIndex]->setAlignment(Qt::AlignCenter);
    sectionHeader[sectionIndex]->setText("Interface Options");
    sectionHeader[sectionIndex]->setStyleSheet("font-weight: bold;");
    sectionHeader[sectionIndex]->setFixedHeight(25);
    gridLayout->addWidget(sectionHeader[sectionIndex],index,0);
    index++;
    sectionIndex++;

    for (i = 0; i<INTERFACE_BINDS; i++){
        keybindDesc[buttonNum] = new QLabel(this);
        keybindDesc[buttonNum]->setText(interfaceKeybindDescName[i]);
        keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
        keybindDesc[buttonNum]->setFixedHeight(25);

        keybind[buttonNum] = new QPushButton(this);
        keybind[buttonNum]->setFixedHeight(25);
        keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("interfaceKeybind%1").arg(i);
        keybind[buttonNum]->setObjectName(objectName);
        connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

        keybindBackup[buttonNum] = new QPushButton(this);
        keybindBackup[buttonNum]->setFixedHeight(25);
        keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("interfaceKeybindBackup%1").arg(i);
        keybindBackup[buttonNum]->setObjectName(objectName);
        connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybindBackup[buttonNum],buttonNum);

        gridLayout->addWidget(keybindDesc[buttonNum],index,0);
        gridLayout->addWidget(keybind[buttonNum],index,1);
        gridLayout->addWidget(keybindBackup[buttonNum],index,2);
        index++;
        buttonNum++;
    }

    //chat section labels
    sectionHeader[sectionIndex] = new QLabel(this);
    sectionHeader[sectionIndex]->setAlignment(Qt::AlignCenter);
    sectionHeader[sectionIndex]->setText("Chat Options");
    sectionHeader[sectionIndex]->setStyleSheet("font-weight: bold;");
    sectionHeader[sectionIndex]->setFixedHeight(25);
    gridLayout->addWidget(sectionHeader[sectionIndex],index,0);
    index++;
    sectionIndex++;

    for (i = 0; i<CHAT_BINDS; i++){
        keybindDesc[buttonNum] = new QLabel(this);
        keybindDesc[buttonNum]->setText(chatKeybindDescName[i]);
        keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
        keybindDesc[buttonNum]->setFixedHeight(25);

        keybind[buttonNum] = new QPushButton(this);
        keybind[buttonNum]->setFixedHeight(25);
        keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("chatKeybind%1").arg(i);
        keybind[buttonNum]->setObjectName(objectName);
        connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

        keybindBackup[buttonNum] = new QPushButton(this);
        keybindBackup[buttonNum]->setFixedHeight(25);
        keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
        objectName = QString("chatKeybindBackup%1").arg(i);
        connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(keybindBackup[buttonNum],buttonNum);

        gridLayout->addWidget(keybindDesc[buttonNum],index,0);
        gridLayout->addWidget(keybind[buttonNum],index,1);
        gridLayout->addWidget(keybindBackup[buttonNum],index,2);
        index++;
        buttonNum++;
    }

    //misc section labels
    sectionHeader[sectionIndex] = new QLabel(this);
    sectionHeader[sectionIndex]->setAlignment(Qt::AlignCenter);
    sectionHeader[sectionIndex]->setText("Misc Options");
    sectionHeader[sectionIndex]->setStyleSheet("font-weight: bold;");
    sectionHeader[sectionIndex]->setFixedHeight(25);
    gridLayout->addWidget(sectionHeader[sectionIndex],index,0);
    index++;
    sectionIndex++;

    keybindDesc[buttonNum] = new QLabel(this);
    keybindDesc[buttonNum]->setText(miscKeybindDescName);
    keybindDesc[buttonNum]->setAlignment(Qt::AlignCenter);
    keybindDesc[buttonNum]->setFixedHeight(25);

    keybind[buttonNum] = new QPushButton(this);
    keybind[buttonNum]->setFixedHeight(25);
    keybind[buttonNum]->setStyleSheet("border: 2px solid black;");
    objectName = QString("miscKeybind%1").arg(i);
    keybind[buttonNum]->setObjectName(objectName);
    connect(keybind[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
    keybindMapperMain->setMapping(keybind[buttonNum],buttonNum);

    keybindBackup[buttonNum] = new QPushButton(this);
    keybindBackup[buttonNum]->setFixedHeight(25);
    keybindBackup[buttonNum]->setStyleSheet("border: 2px solid black;");
     objectName = QString("miscKeybindBackup%1").arg(i);
    keybindBackup[buttonNum]->setObjectName(objectName);
    connect(keybindBackup[buttonNum],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
    keybindMapperMain->setMapping(keybindBackup[buttonNum],buttonNum);

    gridLayout->addWidget(keybindDesc[buttonNum],index,0);
    gridLayout->addWidget(keybind[buttonNum],index,1);
    gridLayout->addWidget(keybindBackup[buttonNum],index,2);
    index++;
    buttonNum++;

    //second frame stuff
    secondFrame = new QFrame(this);
    objectName = "secondFrame";
    secondFrame->setObjectName(objectName);
    secondFrame->setGeometry(0,350,450,100);
    secondFrame->setStyleSheet("#secondFrame{"
                               "border: 2px solid black;}");

    secondLayout = new QHBoxLayout(secondFrame);
    secondLayout->setMargin(0);
    secondLayout->setSpacing(0);

    for(i = 0; i < 4; i++){
        secondFrameV[i] = new QFrame(this);
        secondFrameVLayout[i] = new QVBoxLayout(secondFrameV[i]);
        secondLayout->addWidget(secondFrameV[i]);
        secondFrameVLayout[i]->setContentsMargins(5,10,5,10);
    }
    secondFrameCheckbox[0] = new QCheckBox(this);
    secondFrameCheckbox[0]->setObjectName("Keybind Mode");
    secondFrameCheckbox[0]->setText("Keybind Mode");
    secondFrameCheckbox[0]->resize(115,25);
    secondFrameCheckbox[0]->setMinimumWidth(115);
    secondFrameCheckbox[0]->setStyleSheet("border: none;");
    secondFrameV[0]->setMinimumWidth(115);
    secondFrameVLayout[0]->addWidget(secondFrameCheckbox[0]);


    secondFrameCheckbox[1] = new QCheckBox(this);
    secondFrameCheckbox[1]->setObjectName("Character Specific");
    secondFrameCheckbox[1]->setText("Character Specific");
    secondFrameCheckbox[1]->resize(115,25);
    secondFrameCheckbox[1]->setMinimumWidth(115);
    secondFrameCheckbox[1]->setStyleSheet("border: none;");
    secondFrameVLayout[0]->addWidget(secondFrameCheckbox[1]);


    secondFrameButtons[0] = new QPushButton(this);
    secondFrameButtons[0]->setObjectName("Defaults");
    secondFrameButtons[0]->setText("Defaults");
    secondFrameButtons[0]->setGeometry(135,30,70,40);
    connect(secondFrameButtons[0],SIGNAL(clicked(bool)),this,SIGNAL(defaultBinds()));
    secondFrameVLayout[1]->addWidget(secondFrameButtons[0]);


    secondFrameButtons[1] = new QPushButton(this);
    secondFrameButtons[1]->setObjectName("Remove Bind");
    secondFrameButtons[1]->setText("Remove Bind");
    secondFrameButtons[1]->setGeometry(215,30,70,40);
    secondFrameVLayout[2]->addWidget(secondFrameButtons[1]);


    secondFrameButtons[2] = new QPushButton(this);
    secondFrameButtons[2]->setObjectName("Apply");
    secondFrameButtons[2]->setText("Apply");
    secondFrameButtons[2]->setGeometry(290,30,70,40);
    connect(secondFrameButtons[2],SIGNAL(clicked(bool)),this,SIGNAL(saveBinds()));
    secondFrameVLayout[3]->addWidget(secondFrameButtons[2]);

    secondLayout->setStretch(0,5);
    secondLayout->setStretch(1,1);
    secondLayout->setStretch(2,1);
    secondLayout->setStretch(3,1);
    secondLayout->insertSpacing(1,40);


    //turn it all into a scroll area
    scrollArea->setWidget(mainFrame);
    scrollArea->setGeometry(0,0,450,350);


    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(secondFrame);
    mainLayout->setStretch(0,8);
    mainLayout->setStretch(1,1);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

}

//void KeybindMenu::defaultBinds(){
//}
//void KeybindMenu::removeBinds(){
//}

void KeybindMenu::updateBind(QKeySequence newKeybind, int num){
    qDebug() << "Detected" << newKeybind.toString() << num;
    QString keyText = newKeybind.toString();
    keyText.replace(QString("F31"),"Mouse-Up");
    keyText.replace(QString("F32"),"Mouse-Down");
    keyText.replace(QString("F33"),"Mouse-Mid");
    keyText.replace(QString("F34"),"Mouse-Back");
    keyText.replace(QString("F35"),"Mouse-Forward");
    qDebug() << keyText;

    assert(num >= 0 && num< KEYBINDCOUNT);

    if(num < MOVE_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Move";
    }
    else if(num < COMBAT_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Combat";
    }
    else if(num < TARGET_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Targeting";
    }
    else if(num < CAMERA_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Camera";
    }
    else if(num < ACTION_PRIMARY_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Action Primary";
    }
    else if(num < ACTION_SECONDARY_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Action Secondary";
    }
    else if(num < INTERFACE_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Interface";
    }
    else if(num < CHAT_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Chat";
    }
    else if(num < MISC_BINDS_RANGE){
        keybind[num]->setText(keyText);
        qDebug() << "Setup Misc";
    }

    //check if overwriting other binds by assigning this keyseq
    int i;

    for(i = 0; i< KEYBINDCOUNT; i++){
        if(i != num){
            if(shortcuts[i]->key() == newKeybind){
                qDebug() << "Dupe found at:" << i;
                updateText(i);
            }
        }
    }
}

void KeybindMenu::updateText(int num){
    assert(num >= 0);

    qDebug() << "Updating at:" << num;

    keybind[num]->setText("");
    emit newBindSend(QKeySequence(),num);
}

void KeybindMenu::newBindRecv(QKeySequence newKeybind, int num){
    updateBind(newKeybind,num);
    emit newBindSend(newKeybind,num);
}

void KeybindMenu::copyShortcuts(QShortcut *copyshort[]){
    shortcuts = copyshort;
}

//void KeybindMenu::updateShortcut(){

//}


void KeybindMenu::setBindMain(int num){
    /* design
    popup msg to ask for keybind change
    use event/keyfilter to capture sequence
    emit new keybind back to mainwindow to update
    close window
    */

    if(this->findChild<KeybindDialog*>("keybindDialog")){
        qDebug() << "One is open right now";
        return;
    }
    if(num == 64){
        //cannot rebind esc
        return;
    }
    emit disableShortcuts();

//    for(int i = 0; i < 73; i++){
//        qDebug() << shortcuts[i]->key();
//    }

    KeybindDialog *keybindPrompt = new KeybindDialog(this);
    keybindPrompt->num = num;
    connect(keybindPrompt,SIGNAL(newBind(QKeySequence,int)),this,SLOT(newBindRecv(QKeySequence,int)));
    connect(keybindPrompt,SIGNAL(destroyed(QObject*)),this,SIGNAL(enableShortcuts()));

    qDebug() << "\n\nSetting Keybind Num:" << num;
}

void KeybindMenu::setBindBackup(int num){
    qDebug() << num;
    assert(num >= 0 && num< KEYBINDCOUNT);

    if(num < MOVE_BINDS_RANGE){
        qDebug() << "Setup Move Backup";
    }
    else if(num < COMBAT_BINDS_RANGE){
        qDebug() << "Setup Combat Backup";
    }
    else if(num < TARGET_BINDS_RANGE){
        qDebug() << "Setup Targeting Backup";
    }
    else if(num < CAMERA_BINDS_RANGE){
        qDebug() << "Setup Camera Backup";
    }
    else if(num < ACTION_PRIMARY_BINDS_RANGE){
        qDebug() << "Setup Action Primary Backup";
    }
    else if(num < ACTION_SECONDARY_BINDS_RANGE){
        qDebug() << "Setup Action Secondary Backup";
    }
    else if(num < INTERFACE_BINDS_RANGE){
        qDebug() << "Setup Interface Backup";
    }
    else if(num < CHAT_BINDS_RANGE){
        qDebug() << "Setup Chat Backup";
    }
    else if(num > MISC_BINDS_RANGE){
        qDebug() << "Setup Misc Backup";
    }
}

void KeybindMenu::updateKeybinds(QString *shortcut){
    int i;

    for(i=0 ; i<KEYBINDCOUNT; i++){
        shortcut[i].replace(QString("F31"),"Mouse-Up");
        shortcut[i].replace(QString("F32"),"Mouse-Down");
        shortcut[i].replace(QString("F33"),"Mouse-Mid");
        shortcut[i].replace(QString("F34"),"Mouse-Back");
        shortcut[i].replace(QString("F35"),"Mouse-Forward");
    }  

    for(i=0; i<KEYBINDCOUNT; i++){
        keybind[i]->setText(shortcut[i]);
    }

}

void KeybindMenu::resizeMe(QSize newSize){
    if (newSize == this->size()){
        qDebug() << "returned";
        return;
    }

    if(scrollArea->size().width()-20 > 250){
        mainFrame->resize(scrollArea->size().width()-20,
                          mainFrame->size().height());
    }
    return;
}

