#include "chatbox.h"



Chatbox::Chatbox(QWidget *parent)
    : QFrame(parent)
{
    setGeometry(0,650,200,250);


    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    chatTabs = new QTabWidget(this);

    chatInput = new QTextEdit(this);
    chatInput->setStyleSheet("background-color: rgba(0,0,0,0);");
    chatInput->setMaximumHeight(30);
    chatInput->setText("Type stuff here into chat!");

    mainLayout->addWidget(chatTabs);
    mainLayout->addWidget(chatInput);

    QWidget *mainChatFrame = new QWidget(this);
    mainChatFrame->setObjectName("mainChat");
    mainChatFrame->resize(200,200);

    QTextBrowser *mainChatBrowser = new QTextBrowser(mainChatFrame);
    mainChatBrowser->resize(200,200);

    mainChatBrowser->setText("This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be"
                             "This is a test to see how longg the strings can be");
    chatTabs->addTab(mainChatFrame,mainChatFrame->objectName());
    chatTabFrames.push_back(mainChatFrame);

}

void Chatbox::resizeMe(QSize size){ //fix this too for 1080p
    const double scale_factor_y = (double)700/(double)900;
    const double scale_factor_w = (double)200/(double)1200;
    //const double scale_factor_h = (double)200/(double)900;

    move(0,size.height()*scale_factor_y);
    resize(size.width()*scale_factor_w,size.height()*scale_factor_y);
    qDebug() << this->size() << chatTabs->size() << chatInput->size();
}
