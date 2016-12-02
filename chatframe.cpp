#include "ChatFrame.hpp"

#define FRAME_WIDTH 250
#define FRAME_HEIGHT 250

ChatFrame::ChatFrame(QWidget *parent)
    : QFrame(parent)
{
    setGeometry(0,900-FRAME_HEIGHT,FRAME_WIDTH,FRAME_HEIGHT);
    setObjectName("chatFrame");
    setStyleSheet("border: 1px solid black;");

    chatTabs = new QTabWidget(this);
    chatTabs->setGeometry(0,0,FRAME_WIDTH,220);
    chatTabs->setMaximumHeight(220);

    chatInput = new TextEdit(this);
    chatInput->setStyleSheet("background-color: rgba(0,0,0,0);");
    chatInput->setMaximumHeight(30);
    chatInput->setText("Type stuff here into chat!");
    chatInput->setGeometry(0,220,FRAME_WIDTH,30);
    connect(chatInput,SIGNAL(send()),this,SLOT(handleSend()));

    QWidget *mainChatFrame = new QWidget(this);
    mainChatFrame->setObjectName("Main");
    mainChatFrame->resize(FRAME_WIDTH,220);

    TextBrowser *mainChatBrowser = new TextBrowser(mainChatFrame);
    mainChatBrowser->setObjectName("mainChatBrowser");
    mainChatBrowser->resize(mainChatFrame->size());
    mainChatBrowser->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    mainChatBrowser->setText("This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be");
    chatTabs->addTab(mainChatFrame,mainChatFrame->objectName());
    chatTabFrames.push_back(mainChatFrame);
    chatBrowsers.push_back(mainChatBrowser);

    QWidget *whisperFrame = new QWidget(this);
    whisperFrame->setObjectName("Whispers");
    whisperFrame->resize(FRAME_WIDTH,220);

    TextBrowser *whisperBrowser = new TextBrowser(whisperFrame);
    whisperBrowser->setObjectName("whisperBrowser");
    whisperBrowser->resize(whisperFrame->size());
    whisperBrowser->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    whisperBrowser->setText("Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!"
                            "Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!"
                            "Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!"
                            "Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!"
                            "Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!"
                            "Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!"
                            "Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!"
                            "Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!"
                            "Pssssssssssssssssssssssssssssst Whisper!!!!!!!!!!!!");
    chatTabs->addTab(whisperFrame,whisperFrame->objectName());
    chatTabFrames.push_back(whisperFrame);
    chatBrowsers.push_back(whisperBrowser);

    QWidget *guildFrame = new QWidget(this);
    guildFrame->setObjectName("Guild");
    guildFrame->resize(FRAME_WIDTH,220);

    TextBrowser *guildBrowser = new TextBrowser(guildFrame);
    guildBrowser->setObjectName("guildBrowser");
    guildBrowser->resize(whisperFrame->size());
    guildBrowser->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    guildBrowser->setText("Gchat: Lol We are the best pvpers in the world xDDDDDD"
                          "Gchat: Lol We are the best pvpers in the world xDDDDDD"
                          "Gchat: Lol We are the best pvpers in the world xDDDDDD"
                          "Gchat: Lol We are the best pvpers in the world xDDDDDD"
                          "Gchat: Lol We are the best pvpers in the world xDDDDDD"
                          "Gchat: Lol We are the best pvpers in the world xDDDDDD"
                          "Gchat: Lol We are the best pvpers in the world xDDDDDD"
                          "Gchat: Lol We are the best pvpers in the world xDDDDDD"
                          "Gchat: Lol We are the best pvpers in the world xDDDDDD");
    chatTabs->addTab(guildFrame,guildFrame->objectName());
    chatTabFrames.push_back(guildFrame);
    chatBrowsers.push_back(guildBrowser);

    connect(mainChatBrowser,SIGNAL(resetCursor(uint32_t)),this,SIGNAL(resetCursor(uint32_t)));
    connect(whisperBrowser,SIGNAL(resetCursor(uint32_t)),this,SIGNAL(resetCursor(uint32_t)));
    connect(guildBrowser,SIGNAL(resetCursor(uint32_t)),this,SIGNAL(resetCursor(uint32_t)));

    chatInput->hide();
}


void ChatFrame::handleSend(){
    //handles send here
    qDebug() << "Handle message to send here";
    chatInput->clear();
    chatInput->clearFocus();
    chatInput->hide();
}

void ChatFrame::resizeMe(QSize size){ //fix this too for 1080p
    double scale_factor_y = 650.0/900.0;
    double scale_factor_w = 250.0/900.0;
    double scale_factor_h = 250.0/900.0;

    move(0,size.height()*scale_factor_y);
    resize(size.height()*scale_factor_w,
           size.height()*scale_factor_h);

    scale_factor_y = 220.0/900.0;
    scale_factor_w = 250.0/900.0;
    scale_factor_h = 30.0/900.0;

    chatInput->setGeometry(0,
                           size.height()*scale_factor_y,
                           size.height()*scale_factor_w,
                           size.height()*scale_factor_h);

    scale_factor_h = 220.0/900.0;
    chatTabs->setGeometry(0,0,
                           size.height()*scale_factor_w,
                           size.height()*scale_factor_h);

    scale_factor_h = 200.0/900.0;
    for(int i =0; i < chatTabFrames.count();i++){
        chatTabFrames[i]->resize(size.height()*scale_factor_w,
                                        size.height()*scale_factor_h);
        chatBrowsers[i]->resize(chatTabFrames[i]->size());
    }
    return;
}

bool ChatFrame::inputVisible(){
    return chatInput->isVisible();
}

void ChatFrame::setInputVisible(bool visible)
{
    visible?chatInput->setVisible(true):chatInput->setVisible(false);
}
void ChatFrame::setInputFocus(bool focus){
    focus?chatInput->setFocus():chatInput->clearFocus();
}

