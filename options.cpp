#include "options.hpp"


OptionsFrame::OptionsFrame(QWidget *parent)
    : QFrame(parent)
{
    resize(527,452);
    setObjectName("optionsFrame");
    setStyleSheet("QFrame#optionsFrame{"
                  "border: 2px solid black;"
                  "background-color: white;}");
    move(600 - this->width()/2, 450 - this->height()/2);
    hide();

    mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    buttonFrame = new QFrame(this);
    buttonFrame->setFixedSize(75,450);
    buttonFrame->setObjectName("buttonFrame");
    buttonFrame->setStyleSheet("QFrame#buttonFrame{"
                               "border: 2px solid black;}");

    buttonLayout = new QVBoxLayout(buttonFrame);
    buttonLayout->setSpacing(0);
    buttonLayout->setMargin(0);

    for(int i = 0; i< 6; i++){
        options[i] = new QPushButton(buttonFrame);
        options[i]->setObjectName("optionButtons");
        options[i]->setStyleSheet("border: 2px solid black;");
        options[i]->setFixedSize(75,75);
        options[i]->setIconSize(QSize(50,50));
        switch (i){
            case 0:
               options[i]->setObjectName("Video");
               break;
            case 1:
               options[i]->setObjectName("Sound");
                break;
            case 2:
               options[i]->setObjectName("Gameplay");
                break;
            case 3:
               options[i]->setObjectName("Interface");
                break;
            case 4:
               options[i]->setObjectName("Key Bindings");
                break;
            case 5:
               options[i]->setObjectName("Macros");
                break;
        }
        options[i]->setText(options[i]->objectName());
        connect(options[i],SIGNAL(clicked(bool)),this,SLOT(currentOption()));
        buttonLayout->addWidget(options[i]);
    }
    options[0]->setStyleSheet("border-right: none;");

    optionsStacked = new QStackedWidget(this);
    optionsStacked->setObjectName("stackFrame");
    optionsStacked->setFixedSize(450,450);
    optionsStacked->setStyleSheet("QStackedWidget#stackFrame{"
                                  "border-top: 2px solid black;"
                                  "border-right: 2px solid black;"
                                  "border-bottom: 2px solid black;"
                                  "border-left: none;}");

    mainLayout->addWidget(buttonFrame);
    mainLayout->addWidget(optionsStacked);

    for (int j = 0; j < 6; j++){
        if(j == 4){
            keybindMenu = new KeybindMenu(optionsStacked);
            keybindMenu->resize(450,450);
            connect(keybindMenu,SIGNAL(disableShortcuts()),this,SLOT(disableShortcutsRec()));
            connect(keybindMenu,SIGNAL(enableShortcuts()),this,SLOT(enableShortcutsRec()));
            optionsStacked->addWidget(keybindMenu);
        }

        else{
            optionFrame[j] = new QFrame(optionsStacked);
            optionFrame[j]->resize(450,450);


            switch (j){
                case 0:
                    optionFrame[j]->setObjectName("Video");
                    optionFrame[j]->setStyleSheet("background: solid blue;");
                    break;
                case 1:
                    optionFrame[j]->setObjectName("Sound");
                    optionFrame[j]->setStyleSheet("background: solid red;");
                    break;
                case 2:
                    optionFrame[j]->setObjectName("Gameplay");
                    optionFrame[j]->setStyleSheet("background: solid green;");
                    break;
                case 3:
                    optionFrame[j]->setObjectName("Interface");
                    optionFrame[j]->setStyleSheet("background: solid purple;");
                    break;
                case 4:
                    //do nothing
                    break;
                case 5:
                    optionFrame[j]->setObjectName("Macros");
                    optionFrame[j]->setStyleSheet("background: solid yellow;");
                    break;
            }
            optionsStacked->addWidget(optionFrame[j]);
        }
    }

}
void OptionsFrame::disableShortcutsRec(){
    emit disableShortcutsSend();
}

void OptionsFrame::enableShortcutsRec(){
    emit enableShortcutsSend();
}

void OptionsFrame::currentOption(){
    for(int i = 0; i< 6; i++){
        options[i]->setStyleSheet("border: 2px solid black;");
    }
    if (sender()->objectName() == "Video"){
        optionsStacked->setCurrentIndex(0);
        options[0]->setStyleSheet("border-right: 2px solid white;");
    }
    else if(sender()->objectName() == "Sound"){
        optionsStacked->setCurrentIndex(1);
        options[1]->setStyleSheet("border-right: 2px solid white;");
    }
    else if(sender()->objectName() == "Gameplay"){
        optionsStacked->setCurrentIndex(2);
        options[2]->setStyleSheet("border-right: 2px solid white;");
    }
    else if(sender()->objectName() == "Interface"){
        optionsStacked->setCurrentIndex(3);
        options[3]->setStyleSheet("border-right: 2px solid white;");
    }
    else if(sender()->objectName() == "Key Bindings"){
        optionsStacked->setCurrentIndex(4);
        options[4]->setStyleSheet("border-right: 2px solid white;");
    }
    else if(sender()->objectName() == "Macros"){
        optionsStacked->setCurrentIndex(5);
        options[5]->setStyleSheet("border-right: 2px solid white;");
    }
}

void OptionsFrame::updateKeybinds(QString *keybinds){
    keybindMenu->updateKeybinds(keybinds);
}
