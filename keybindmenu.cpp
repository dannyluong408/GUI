#include "keybindmenu.hpp"

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

    gridLayout = new QGridLayout(mainFrame);
    gridLayout->setMargin(10);
    gridLayout->setSpacing(10);

    gridLayout->setColumnMinimumWidth(0,180);
    gridLayout->setColumnMinimumWidth(1,100);
    gridLayout->setColumnMinimumWidth(2,100);
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

    for (i = 0; i<7; i++){
        moveKeybindDesc[i] = new QLabel(this);
        moveKeybindDesc[i]->setText(moveKeybindDescName[i]);
        moveKeybindDesc[i]->setAlignment(Qt::AlignCenter);
        moveKeybindDesc[i]->setFixedHeight(25);

        moveKeybind[i] = new QPushButton(this);
        moveKeybind[i]->setFixedHeight(25);
        moveKeybind[i]->setStyleSheet("border: 2px solid black;");
        objectName = "moveKeybind" + i;
        moveKeybind[i]->setObjectName(objectName);
        connect(moveKeybind[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(moveKeybind[i],buttonNum);

        moveKeybindBackup[i] = new QPushButton(this);
        moveKeybindBackup[i]->setFixedHeight(25);
        moveKeybindBackup[i]->setStyleSheet("border: 2px solid black;");
        objectName = "moveKeybindBackup" + i;
        moveKeybindBackup[i]->setObjectName(objectName);
        connect(moveKeybindBackup[i],SIGNAL(clicked()),keybindMapperBackup,SLOT(map()));
        keybindMapperBackup->setMapping(moveKeybindBackup[i],buttonNum);

        gridLayout->addWidget(moveKeybindDesc[i],index,0);
        gridLayout->addWidget(moveKeybind[i],index,1);
        gridLayout->addWidget(moveKeybindBackup[i],index,2);
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

    combatKeybindDesc = new QLabel(this);
    combatKeybindDesc->setText(combatKeybindDescName);
    combatKeybindDesc->setAlignment(Qt::AlignCenter);
    combatKeybindDesc->setFixedHeight(25);

    combatKeybind = new QPushButton(this);
    combatKeybind->setFixedHeight(25);
    combatKeybind->setStyleSheet("border: 2px solid black;");
    objectName = "combatKeybind";
    combatKeybind->setObjectName(objectName);
    connect(combatKeybind,SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
    keybindMapperMain->setMapping(combatKeybind,buttonNum);

    combatKeybindBackup = new QPushButton(this);
    combatKeybindBackup->setFixedHeight(25);
    combatKeybindBackup->setStyleSheet("border: 2px solid black;");
    objectName = "combatKeybindBackup";
    combatKeybindBackup->setObjectName(objectName);
    connect(combatKeybindBackup,SIGNAL(clicked()),keybindMapperBackup,SLOT(map()));
    keybindMapperBackup->setMapping(combatKeybindBackup,buttonNum);


    gridLayout->addWidget(combatKeybindDesc,index,0);
    gridLayout->addWidget(combatKeybind,index,1);
    gridLayout->addWidget(combatKeybindBackup,index,2);
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

    for (i = 0; i<30; i++){
        targetingKeybindDesc[i] = new QLabel(this);
        targetingKeybindDesc[i]->setText(targetingKeybindDescName[i]);
        targetingKeybindDesc[i]->setAlignment(Qt::AlignCenter);
        targetingKeybindDesc[i]->setFixedHeight(25);

        targetingKeybind[i] = new QPushButton(this);
        targetingKeybind[i]->setFixedHeight(25);
        targetingKeybind[i]->setStyleSheet("border: 2px solid black;");
        objectName = "targetingKeybind";
        targetingKeybind[i]->setObjectName(objectName);
        connect(targetingKeybind[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(targetingKeybind[i],buttonNum);

        targetingKeybindBackup[i] = new QPushButton(this);
        targetingKeybindBackup[i]->setFixedHeight(25);
        targetingKeybindBackup[i]->setStyleSheet("border: 2px solid black;");
        objectName = "targetingKeybindBackup";
        targetingKeybindBackup[i]->setObjectName(objectName);
        connect(targetingKeybindBackup[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(targetingKeybindBackup[i],buttonNum);

        gridLayout->addWidget(targetingKeybindDesc[i],index,0);
        gridLayout->addWidget(targetingKeybind[i],index,1);
        gridLayout->addWidget(targetingKeybindBackup[i],index,2);
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

    for (i = 0; i<3; i++){
        cameraKeybindDesc[i] = new QLabel(this);
        cameraKeybindDesc[i]->setText(cameraKeybindDescName[i]);
        cameraKeybindDesc[i]->setAlignment(Qt::AlignCenter);
        cameraKeybindDesc[i]->setFixedHeight(25);

        cameraKeybind[i] = new QPushButton(this);
        cameraKeybind[i]->setFixedHeight(25);
        cameraKeybind[i]->setStyleSheet("border: 2px solid black;");
        objectName = "cameraKeybind"+i;
        cameraKeybind[i]->setObjectName(objectName);
        connect(cameraKeybind[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(cameraKeybind[i],buttonNum);

        cameraKeybindBackup[i] = new QPushButton(this);
        cameraKeybindBackup[i]->setFixedHeight(25);
        cameraKeybindBackup[i]->setStyleSheet("border: 2px solid black;");
        objectName = "cameraKeybindBackup";
        cameraKeybindBackup[i]->setObjectName(objectName);
        connect(cameraKeybindBackup[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(cameraKeybindBackup[i],buttonNum);

        gridLayout->addWidget(cameraKeybindDesc[i],index,0);
        gridLayout->addWidget(cameraKeybind[i],index,1);
        gridLayout->addWidget(cameraKeybindBackup[i],index,2);
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

    for (i = 0; i<10; i++){
        actionPrimaryButtonKeybindDesc[i] = new QLabel(this);
        actionPrimaryButtonKeybindDesc[i]->setText(actionPrimaryButtonKeybindDescName[i]);
        actionPrimaryButtonKeybindDesc[i]->setAlignment(Qt::AlignCenter);
        actionPrimaryButtonKeybindDesc[i]->setFixedHeight(25);

        actionPrimaryButtonKeybind[i] = new QPushButton(this);
        actionPrimaryButtonKeybind[i]->setFixedHeight(25);
        actionPrimaryButtonKeybind[i]->setStyleSheet("border: 2px solid black;");
        objectName = "actionPrimaryButtonKeybind"+i;
        actionPrimaryButtonKeybind[i]->setObjectName(objectName);
        connect(actionPrimaryButtonKeybind[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(actionPrimaryButtonKeybind[i],buttonNum);

        actionPrimaryButtonKeybindBackup[i] = new QPushButton(this);
        actionPrimaryButtonKeybindBackup[i]->setFixedHeight(25);
        actionPrimaryButtonKeybindBackup[i]->setStyleSheet("border: 2px solid black;");
        objectName = "actionPrimaryButtonKeybindBackup"+i;
        actionPrimaryButtonKeybindBackup[i]->setObjectName(objectName);
        connect(actionPrimaryButtonKeybindBackup[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(actionPrimaryButtonKeybindBackup[i],buttonNum);

        gridLayout->addWidget(actionPrimaryButtonKeybindDesc[i],index,0);
        gridLayout->addWidget(actionPrimaryButtonKeybind[i],index,1);
        gridLayout->addWidget(actionPrimaryButtonKeybindBackup[i],index,2);
        index++;
        buttonNum++;
    }

    for (i = 0; i<10; i++){
        actionSecondaryButtonKeybindDesc[i] = new QLabel(this);
        actionSecondaryButtonKeybindDesc[i]->setText(actionSecondaryButtonKeybindDescName[i]);
        actionSecondaryButtonKeybindDesc[i]->setAlignment(Qt::AlignCenter);
        actionSecondaryButtonKeybindDesc[i]->setFixedHeight(25);

        actionSecondaryButtonKeybind[i] = new QPushButton(this);
        actionSecondaryButtonKeybind[i]->setFixedHeight(25);
        actionSecondaryButtonKeybind[i]->setStyleSheet("border: 2px solid black;");
        objectName = "actionSecondaryButtonKeybind"+i;
        actionSecondaryButtonKeybind[i]->setObjectName(objectName);
        connect(actionSecondaryButtonKeybind[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(actionSecondaryButtonKeybind[i],buttonNum);

        actionSecondaryButtonKeybindBackup[i] = new QPushButton(this);
        actionSecondaryButtonKeybindBackup[i]->setFixedHeight(25);
        actionSecondaryButtonKeybindBackup[i]->setStyleSheet("border: 2px solid black;");
        objectName = "actionSecondaryButtonKeybindBackup"+i;
        actionSecondaryButtonKeybindBackup[i]->setObjectName(objectName);
        connect(actionSecondaryButtonKeybindBackup[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(actionSecondaryButtonKeybindBackup[i],buttonNum);

        gridLayout->addWidget(actionSecondaryButtonKeybindDesc[i],index,0);
        gridLayout->addWidget(actionSecondaryButtonKeybind[i],index,1);
        gridLayout->addWidget(actionSecondaryButtonKeybindBackup[i],index,2);
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

    for (i = 0; i<8; i++){
        interfaceKeybindDesc[i] = new QLabel(this);
        interfaceKeybindDesc[i]->setText(interfaceKeybindDescName[i]);
        interfaceKeybindDesc[i]->setAlignment(Qt::AlignCenter);
        interfaceKeybindDesc[i]->setFixedHeight(25);

        interfaceKeybind[i] = new QPushButton(this);
        interfaceKeybind[i]->setFixedHeight(25);
        interfaceKeybind[i]->setStyleSheet("border: 2px solid black;");
        objectName = "interfaceKeybind"+i;
        interfaceKeybind[i]->setObjectName(objectName);
        connect(interfaceKeybind[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(interfaceKeybind[i],buttonNum);

        interfaceKeybindBackup[i] = new QPushButton(this);
        interfaceKeybindBackup[i]->setFixedHeight(25);
        interfaceKeybindBackup[i]->setStyleSheet("border: 2px solid black;");
        objectName = "interfaceKeybindBackup"+i;
        interfaceKeybindBackup[i]->setObjectName(objectName);
        connect(interfaceKeybindBackup[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(interfaceKeybindBackup[i],buttonNum);

        gridLayout->addWidget(interfaceKeybindDesc[i],index,0);
        gridLayout->addWidget(interfaceKeybind[i],index,1);
        gridLayout->addWidget(interfaceKeybindBackup[i],index,2);
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

    for (i = 0; i<3; i++){
        chatKeybindDesc[i] = new QLabel(this);
        chatKeybindDesc[i]->setText(chatKeybindDescName[i]);
        chatKeybindDesc[i]->setAlignment(Qt::AlignCenter);
        chatKeybindDesc[i]->setFixedHeight(25);

        chatKeybind[i] = new QPushButton(this);
        chatKeybind[i]->setFixedHeight(25);
        chatKeybind[i]->setStyleSheet("border: 2px solid black;");
        objectName = "chatKeybind"+i;
        chatKeybind[i]->setObjectName(objectName);
        connect(chatKeybind[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(chatKeybind[i],buttonNum);

        chatKeybindBackup[i] = new QPushButton(this);
        chatKeybindBackup[i]->setFixedHeight(25);
        chatKeybindBackup[i]->setStyleSheet("border: 2px solid black;");
        objectName = "chatKeybindBackup"+i;
        chatKeybindBackup[i]->setObjectName(objectName);
        connect(chatKeybindBackup[i],SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
        keybindMapperMain->setMapping(chatKeybindBackup[i],buttonNum);

        gridLayout->addWidget(chatKeybindDesc[i],index,0);
        gridLayout->addWidget(chatKeybind[i],index,1);
        gridLayout->addWidget(chatKeybindBackup[i],index,2);
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

    miscKeybindDesc = new QLabel(this);
    miscKeybindDesc->setText(miscKeybindDescName);
    miscKeybindDesc->setAlignment(Qt::AlignCenter);
    miscKeybindDesc->setFixedHeight(25);

    miscKeybind = new QPushButton(this);
    miscKeybind->setFixedHeight(25);
    miscKeybind->setStyleSheet("border: 2px solid black;");
    objectName = "miscKeybind"+i;
    miscKeybind->setObjectName(objectName);
    connect(miscKeybind,SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
    keybindMapperMain->setMapping(miscKeybind,buttonNum);

    miscKeybindBackup = new QPushButton(this);
    miscKeybindBackup->setFixedHeight(25);
    miscKeybindBackup->setStyleSheet("border: 2px solid black;");
    objectName = "miscKeybindBackup"+i;
    miscKeybindBackup->setObjectName(objectName);
    connect(miscKeybindBackup,SIGNAL(clicked()),keybindMapperMain,SLOT(map()));
    keybindMapperMain->setMapping(miscKeybindBackup,buttonNum);

    gridLayout->addWidget(miscKeybindDesc,index,0);
    gridLayout->addWidget(miscKeybind,index,1);
    gridLayout->addWidget(miscKeybindBackup,index,2);
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

    for(i = 0; i < 5; i++){
        secondFrameV[i] = new QFrame(this);
        secondFrameVLayout[i] = new QVBoxLayout(secondFrameV[i]);
        secondLayout->addWidget(secondFrameV[i]);
        secondFrameVLayout[i]->setContentsMargins(5,10,5,10);
    }
    secondFrameCheckbox[0] = new QCheckBox(this);
    secondFrameCheckbox[0]->setObjectName("Keybind Mode");
    secondFrameCheckbox[0]->setText("Keybind Mode");
    secondFrameCheckbox[0]->setGeometry(10,20,115,25);
    secondFrameCheckbox[0]->setStyleSheet("border: none;");
    secondFrameVLayout[0]->addWidget(secondFrameCheckbox[0]);

    secondFrameCheckbox[1] = new QCheckBox(this);
    secondFrameCheckbox[1]->setObjectName("Character Specific");
    secondFrameCheckbox[1]->setText("Character Specific");
    secondFrameCheckbox[1]->setGeometry(10,55,115,25);
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


    secondFrameButtons[3] = new QPushButton(this);
    secondFrameButtons[3]->setObjectName("Cancel");
    secondFrameButtons[3]->setText("Cancel");
    secondFrameButtons[3]->setGeometry(365,30,70,40);
    secondFrameVLayout[4]->addWidget(secondFrameButtons[3]);


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
    //qDebug() << newKeybind.toString() << num;
    if(num < 0){
        qDebug() << "Error";
    }
    else if(num < 7){
        moveKeybind[num]->setText(newKeybind.toString());
        qDebug() << "Setup Move";
    }
    else if(num == 7){
        combatKeybind->setText(newKeybind.toString());
        qDebug() << "Setup Combat";
    }
    else if(num < 38){
        targetingKeybind[num-7]->setText(newKeybind.toString());
        qDebug() << "Setup Targeting";
    }
    else if(num < 41){
        cameraKeybind[num-38]->setText(newKeybind.toString());
        qDebug() << "Setup Camera";
    }
    else if(num < 51){
        actionPrimaryButtonKeybind[num-41]->setText(newKeybind.toString());
        qDebug() << "Setup Action Primary";
    }
    else if(num < 61){
        actionSecondaryButtonKeybind[num-51]->setText(newKeybind.toString());
        qDebug() << "Setup Action Secondary";
    }
    else if(num < 69){
        interfaceKeybind[num-61]->setText(newKeybind.toString());
        qDebug() << "Setup Interface";
    }
    else if(num < 72){
        chatKeybind[num-69]->setText(newKeybind.toString());
        qDebug() << "Setup Chat";
    }
    else if(num == 72){
        miscKeybind->setText(newKeybind.toString());
        qDebug() << "Setup Misc";
    }

    //check if overwriting other binds by assigning this keyseq
    int i,index = 0;

    for(i=0; i<7; i++){
        if (index == num){
            index++;
        }
        else{
            if(moveKeybind[i]->text() == newKeybind.toString()){
                qDebug() << "Same Bind" << index << num;
                moveKeybind[i]->setText("");
                //emit signal here to update shortkey
                emit newBindSend(QKeySequence(),index);
            }
            index++;
        }
    }


    if (index == num){
        index++;
    }
    else{
        if(combatKeybind->text() == newKeybind.toString()){
            qDebug() << "Same Bind" << index << num;
            combatKeybind->setText("");
            //emit signal here to update shortkey
            emit newBindSend(QKeySequence(),index);
        }
        index++;
    }

    for(i=0; i<30; i++){
        if (index == num){
            index++;
        }
        else{
            if(targetingKeybind[i]->text() == newKeybind.toString()){
                qDebug() << "Same Bind" << index << num;
                targetingKeybind[i]->setText("");
                //emit signal here to update shortkey
                emit newBindSend(QKeySequence(),index);
            }
            index++;
        }
    }
    for(i=0; i<3; i++){
        if (index == num){
            index++;
        }
        else{
            if(cameraKeybind[i]->text() == newKeybind.toString()){
                qDebug() << "Same Bind" << index << num;
                cameraKeybind[i]->setText("");
                //emit signal here to update shortkey
                emit newBindSend(QKeySequence(),index);
            }
            index++;
        }
    }
    for(i=0; i<10; i++){
        if (index == num){
            index++;
        }
        else{
            if(actionPrimaryButtonKeybind[i]->text() == newKeybind.toString()){
                qDebug() << "Same Bind" << index << num;
                actionPrimaryButtonKeybind[i]->setText("");
                //emit signal here to update shortkey
                emit newBindSend(QKeySequence(),index);
            }
            index++;
        }
    }
    for(i=0; i<10; i++){
        if (index == num){
            index++;
        }
        else{
            if(actionSecondaryButtonKeybind[i]->text() == newKeybind.toString()){
                qDebug() << "Same Bind" << index << num;
                actionSecondaryButtonKeybind[i]->setText("");
                //emit signal here to update shortkey
                emit newBindSend(QKeySequence(),index);
            }
            index++;
        }
    }
    for(i=0; i<8; i++){
        if (index == num){
            index++;
        }
        else{
            if(interfaceKeybind[i]->text() == newKeybind.toString()){
                qDebug() << "Same Bind" << index << num;
                interfaceKeybind[i]->setText("");
                //emit signal here to update shortkey
                emit newBindSend(QKeySequence(),index);
            }
            index++;
        }
    }
    for(i=0; i<3; i++){
        if (index == num){
            index++;
        }
        else{
            if(chatKeybind[i]->text() == newKeybind.toString()){
                qDebug() << "Same Bind" << index << num;
                chatKeybind[i]->setText("");
                //emit signal here to update shortkey
                emit newBindSend(QKeySequence(),index);
            }
            index++;
        }
    }

    if (index == num){
        index++;
    }
    else{
        if(miscKeybind->text() == newKeybind.toString()){
            qDebug() << "Same Bind" << index << num;
            miscKeybind->setText("");
            //emit signal here to update shortkey
            emit newBindSend(QKeySequence(),index);
        }
    }
}

void KeybindMenu::newBindRecv(QKeySequence newKeybind, int num){
    updateBind(newKeybind,num);
    emit newBindSend(newKeybind,num);
}

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
    emit disableShortcuts();
    KeybindDialog *keybindPrompt = new KeybindDialog(this);
    keybindPrompt->num = num;
    connect(keybindPrompt,SIGNAL(newBind(QKeySequence,int)),this,SLOT(newBindRecv(QKeySequence,int)));
    connect(keybindPrompt,SIGNAL(destroyed(QObject*)),this,SIGNAL(enableShortcuts()));

    qDebug() << "\n\nSetting Keybind Num:" << num;
}

void KeybindMenu::setBindBackup(int num){
    qDebug() << num;
    if(num < 0){
        qDebug() << "Error";
    }
    else if(num < 7){
        qDebug() << "Setup Move Backup";
    }
    else if(num == 7){
        qDebug() << "Setup Combat Backup";
    }
    else if(num < 38){
        qDebug() << "Setup Targeting Backup";
    }
    else if(num < 41){
        qDebug() << "Setup Camera Backup";
    }
    else if(num < 51){
        qDebug() << "Setup Action Primary Backup";
    }
    else if(num < 61){
        qDebug() << "Setup Action Secondary Backup";
    }
    else if(num < 69){
        qDebug() << "Setup Interface Backup";
    }
    else if(num < 72){
        qDebug() << "Setup Chat Backup";
    }
    else if(num == 72){
        qDebug() << "Setup Misc Backup";
    }
}

void KeybindMenu::updateKeybinds(QString *shortcut){
    int i,index = 0;

    for(i=0; i<7; i++){
        moveKeybind[i]->setText(shortcut[index]);
        index++;
    }

    combatKeybind->setText(shortcut[index]);
    index++;

    for(i=0; i<30; i++){
        targetingKeybind[i]->setText(shortcut[index]);
        index++;
    }
    for(i=0; i<3; i++){
        cameraKeybind[i]->setText(shortcut[index]);
        index++;
    }
    for(i=0; i<10; i++){
        actionPrimaryButtonKeybind[i]->setText(shortcut[index]);
        index++;
    }
    for(i=0; i<10; i++){
        actionSecondaryButtonKeybind[i]->setText(shortcut[index]);
        index++;
    }
    for(i=0; i<8; i++){
        interfaceKeybind[i]->setText(shortcut[index]);
        index++;
    }
    for(i=0; i<3; i++){
        chatKeybind[i]->setText(shortcut[index]);
        index++;
    }

    miscKeybind->setText(shortcut[index]);
}

void KeybindMenu::resizeMe(QSize newSize){
    if (newSize == this->size()){
        qDebug() << "returned";
        return;
    }

    qDebug() << "This is getting called!";
    double scale_factor_w = 415.0/1200.0;
    double scale_factor_h = 350.0/900.0;

    mainFrame->resize(newSize.width()*scale_factor_w,
               mainFrame->size().height());

    scale_factor_w = 450.0/1200.0;
    scrollArea->resize(newSize.width()*scale_factor_w,
                       scrollArea->size().height());
//    scale_factor_w = 450.0/1200.0;
//    scale_factor_h = 100.0/900.0;

//    secondFrame->resize(newSize.width()*scale_factor_w,
//               newSize.height()*scale_factor_h);

//    scale_factor_w = 430.0/1200.0;
//    scale_factor_h = 350.0/900.0;

//    scrollArea->resize(newSize.width()*scale_factor_w,
//               newSize.height()*scale_factor_h);

    qDebug() << "End";
    return;
}
