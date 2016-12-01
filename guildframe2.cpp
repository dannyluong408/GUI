#include "guildframe2.hpp"

GuildFrame2::GuildFrame2(QWidget *parent)
    : QFrame(parent)
{
    setObjectName("guildFrame2");
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    setGeometry(200,200,300,400);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
    Frame1 = new QFrame(this);
    Frame1->setObjectName(QStringLiteral("Frame1"));
    Frame1->setFrameShape(QFrame::StyledPanel);
    Frame1->setFrameShadow(QFrame::Raised);
    horizontalLayout_3 = new QHBoxLayout(Frame1);
    horizontalLayout_3->setSpacing(0);
    horizontalLayout_3->setContentsMargins(0,0,0,0);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
    Icon = new QLabel(Frame1);
    Icon->setObjectName(QStringLiteral("Icon"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Icon->setSizePolicy(sizePolicy);
    Icon->setFixedSize(40,40);
    Icon->setPixmap(QPixmap(":/ui/images/panda.jpg").scaled(40,40,Qt::KeepAspectRatio));

    horizontalLayout_3->addWidget(Icon);
    horizontalLayout_3->setStretch(0,2);
    horizontalLayout_3->setStretch(1,1);

    subFrame1 = new QFrame(Frame1);
    subFrame1->setObjectName(QStringLiteral("subFrame1"));
    subFrame1->setFrameShape(QFrame::StyledPanel);
    subFrame1->setFrameShadow(QFrame::Raised);
    verticalLayout_2 = new QVBoxLayout(subFrame1);
    verticalLayout_2->setSpacing(0);
    verticalLayout_2->setContentsMargins(0,0,0,0);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    titleFrame = new QFrame(subFrame1);
    titleFrame->setObjectName(QStringLiteral("titleFrame"));
    titleFrame->setFrameShape(QFrame::StyledPanel);
    titleFrame->setFrameShadow(QFrame::Raised);
    horizontalLayout_4 = new QHBoxLayout(titleFrame);
    horizontalLayout_4->setSpacing(0);
    horizontalLayout_4->setContentsMargins(0,0,0,0);
    horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
    horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
    Title = new QLabel(titleFrame);
    Title->setObjectName(QStringLiteral("Title"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(Title->sizePolicy().hasHeightForWidth());
    Title->setSizePolicy(sizePolicy1);
    Title->setBaseSize(QSize(245, 25));
    Title->setAlignment(Qt::AlignCenter);

    horizontalLayout_4->addWidget(Title);

    XOut = new QPushButton(titleFrame);
    XOut->setObjectName(QStringLiteral("XOut"));
    sizePolicy.setHeightForWidth(XOut->sizePolicy().hasHeightForWidth());
    XOut->setSizePolicy(sizePolicy);
    XOut->setBaseSize(QSize(15, 15));
    XOut->setMinimumSize(15,15);

    horizontalLayout_4->addWidget(XOut);

    horizontalLayout_4->setStretch(0, 9);
    horizontalLayout_4->setStretch(1, 1);

    verticalLayout_2->addWidget(titleFrame);

    buttonFrame = new QFrame(subFrame1);
    buttonFrame->setObjectName(QStringLiteral("buttonFrame"));
    buttonFrame->setBaseSize(QSize(75, 15));
    buttonFrame->setFrameShape(QFrame::StyledPanel);
    buttonFrame->setFrameShadow(QFrame::Raised);
    horizontalLayout_5 = new QHBoxLayout(buttonFrame);
    horizontalLayout_5->setSpacing(0);
    horizontalLayout_5->setContentsMargins(0,0,0,0);
    horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    information = new QPushButton(buttonFrame);
    information->setObjectName(QStringLiteral("information"));
    sizePolicy.setHeightForWidth(information->sizePolicy().hasHeightForWidth());
    information->setSizePolicy(sizePolicy);
    information->setFixedSize(QSize(65, 15));
    information->setMinimumWidth(65);
    information->setText("Information");
    horizontalLayout_5->addWidget(information);

    settings = new QPushButton(buttonFrame);
    settings->setObjectName(QStringLiteral("settings"));
    sizePolicy.setHeightForWidth(settings->sizePolicy().hasHeightForWidth());
    settings->setSizePolicy(sizePolicy);
    settings->setFixedSize(QSize(45, 15));
    settings->setMinimumWidth(45);
    settings->setText("Settings");
    horizontalLayout_5->addWidget(settings);

    addmember = new QPushButton(buttonFrame);
    addmember->setObjectName(QStringLiteral("addmember"));
    sizePolicy.setHeightForWidth(addmember->sizePolicy().hasHeightForWidth());
    addmember->setSizePolicy(sizePolicy);
    addmember->setFixedSize(QSize(65, 15));
    addmember->setMinimumWidth(65);
    addmember->setText("Add Member");
    horizontalLayout_5->addWidget(addmember);

    hSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_5->addItem(hSpacer);
    horizontalLayout_5->setStretch(0,2);
    horizontalLayout_5->setStretch(1,1);
    horizontalLayout_5->setStretch(2,2);
    horizontalLayout_5->setStretch(3,1);

    verticalLayout_2->addWidget(buttonFrame);

    verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

    verticalLayout_2->addItem(verticalSpacer);


    horizontalLayout_3->addWidget(subFrame1);


    mainLayout->addWidget(Frame1);

    Frame2 = new QFrame(this);
    Frame2->setObjectName(QStringLiteral("Frame2"));
    Frame2->setFrameShape(QFrame::StyledPanel);
    Frame2->setFrameShadow(QFrame::Raised);
    horizontalLayout_2 = new QHBoxLayout(Frame2);
    horizontalLayout_2->setSpacing(0);
    horizontalLayout_2->setContentsMargins(0,0,0,0);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    tableView = new QTableView(Frame2);
    tableView->setObjectName(QStringLiteral("tableView"));
    tableView->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    tableView->setMaximumSize(QSize(897979, 16777215));
    tableView->setBaseSize(QSize(280, 230));

    horizontalLayout_2->addWidget(tableView);


    mainLayout->addWidget(Frame2);

    Frame3 = new QFrame(this);
    Frame3->setObjectName(QStringLiteral("Frame3"));
    Frame3->setBaseSize(QSize(300, 25));
    Frame3->setFrameShape(QFrame::StyledPanel);
    Frame3->setFrameShadow(QFrame::Raised);
    horizontalLayout = new QHBoxLayout(Frame3);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(0,0,0,0);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    label = new QLabel(Frame3);
    label->setObjectName(QStringLiteral("label"));
    label->setBaseSize(QSize(100, 15));

    horizontalLayout->addWidget(label);

    showoffline = new QCheckBox(Frame3);
    showoffline->setObjectName(QStringLiteral("showoffline"));

    horizontalLayout->addWidget(showoffline);


    mainLayout->addWidget(Frame3);

    Frame4 = new QFrame(this);
    Frame4->setObjectName(QStringLiteral("Frame4"));
    Frame4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    Frame4->setFrameShape(QFrame::StyledPanel);
    Frame4->setFrameShadow(QFrame::Raised);
    verticalLayout_3 = new QVBoxLayout(Frame4);
    verticalLayout_3->setSpacing(0);
    verticalLayout_3->setContentsMargins(0,0,0,0);
    verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
    textBrowser = new QTextBrowser(Frame4);
    textBrowser->setObjectName(QStringLiteral("textBrowser"));
    textBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    textBrowser->setSizeIncrement(QSize(0, 0));
    textBrowser->setBaseSize(QSize(280, 90));
    textBrowser->setStyleSheet(QStringLiteral("border-color: rgb(255, 255, 255);"));

    verticalLayout_3->addWidget(textBrowser);


    mainLayout->addWidget(Frame4);

    mainLayout->setStretch(0, 1);
    mainLayout->setStretch(1, 9);
    mainLayout->setStretch(2, 1);
    mainLayout->setStretch(3, 1);

    Icon->setText(QString());
    Title->setText("Both My Dads Play Druids");
    XOut->setText("X");
    label->setText("Online Now: 1/3");
    showoffline->setText("showoffline");
    textBrowser->setPlaceholderText(QString("GMOTD: Welcome to Both My Dads Play Druids!"));

    hide();
}

void GuildFrame2::resizeMe(QSize newSize){
    double scale_x = 300.0/1200.0;
    double scale_y = 400.0/1080.0;
    double scale;
    double new_w = newSize.width();
    double new_h = newSize.height();

    //parent frame
    resize(new_w*scale_x,
           new_h*scale_y);

    if (new_w < new_h){
        scale = 40.0/1200.0;
    }
    else{
        scale = 40.0/1080.0;
    }
    Icon->setFixedSize(new_h*scale,
                         new_h*scale);
    Icon->resize(new_h*scale,
                 new_h*scale);

    //Resize Fonts
    QFont font = Title->font();

    if (new_w < 800.0){
            font.setPointSize(7);
    }
    else{
            font.setPointSize(8);
    }
    Title->setFont(font);
    information->setFont(font);
    settings->setFont(font);
    addmember->setFont(font);

}
