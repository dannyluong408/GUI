#include "guildframe2.hpp"

GuildFrame2::GuildFrame2(QWidget *parent)
    : QFrame(parent)
{
    setObjectName("guildFrame2");
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    setGeometry(200,200,300,400);

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0,0,0,0);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    frame_3 = new QFrame(this);
    frame_3->setObjectName(QStringLiteral("frame_3"));
    frame_3->setFrameShape(QFrame::StyledPanel);
    frame_3->setFrameShadow(QFrame::Raised);
    horizontalLayout_3 = new QHBoxLayout(frame_3);
    horizontalLayout_3->setSpacing(0);
    horizontalLayout_3->setContentsMargins(0,0,0,0);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
    Icon = new QLabel(frame_3);
    Icon->setObjectName(QStringLiteral("Icon"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(Icon->sizePolicy().hasHeightForWidth());
    Icon->setSizePolicy(sizePolicy);
    Icon->setMaximumSize(QSize(100, 100));
    Icon->setBaseSize(QSize(25, 25));
    Icon->setPixmap(QPixmap(":/ui/images/panda.jpg").scaled(25,25,Qt::KeepAspectRatio));
    Icon->setScaledContents(true);

    horizontalLayout_3->addWidget(Icon);

    frame_5 = new QFrame(frame_3);
    frame_5->setObjectName(QStringLiteral("frame_5"));
    frame_5->setFrameShape(QFrame::StyledPanel);
    frame_5->setFrameShadow(QFrame::Raised);
    verticalLayout_2 = new QVBoxLayout(frame_5);
    verticalLayout_2->setSpacing(0);
    verticalLayout_2->setContentsMargins(0,0,0,0);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    frame_6 = new QFrame(frame_5);
    frame_6->setObjectName(QStringLiteral("frame_6"));
    frame_6->setFrameShape(QFrame::StyledPanel);
    frame_6->setFrameShadow(QFrame::Raised);
    horizontalLayout_4 = new QHBoxLayout(frame_6);
    horizontalLayout_4->setSpacing(0);
    horizontalLayout_4->setContentsMargins(0,0,0,0);
    horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
    horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
    Title = new QLabel(frame_6);
    Title->setObjectName(QStringLiteral("Title"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(Title->sizePolicy().hasHeightForWidth());
    Title->setSizePolicy(sizePolicy1);
    Title->setBaseSize(QSize(245, 25));
    Title->setAlignment(Qt::AlignCenter);

    horizontalLayout_4->addWidget(Title);

    XOut = new QPushButton(frame_6);
    XOut->setObjectName(QStringLiteral("XOut"));
    sizePolicy.setHeightForWidth(XOut->sizePolicy().hasHeightForWidth());
    XOut->setSizePolicy(sizePolicy);
    XOut->setBaseSize(QSize(15, 15));

    horizontalLayout_4->addWidget(XOut);

    horizontalLayout_4->setStretch(0, 9);
    horizontalLayout_4->setStretch(1, 1);

    verticalLayout_2->addWidget(frame_6);

    frame_7 = new QFrame(frame_5);
    frame_7->setObjectName(QStringLiteral("frame_7"));
    frame_7->setBaseSize(QSize(75, 15));
    frame_7->setFrameShape(QFrame::StyledPanel);
    frame_7->setFrameShadow(QFrame::Raised);
    horizontalLayout_5 = new QHBoxLayout(frame_7);
    horizontalLayout_5->setSpacing(0);
    horizontalLayout_5->setContentsMargins(0,0,0,0);
    horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    pushButton_4 = new QPushButton(frame_7);
    pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
    sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
    pushButton_4->setSizePolicy(sizePolicy);

    horizontalLayout_5->addWidget(pushButton_4);

    pushButton_2 = new QPushButton(frame_7);
    pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
    sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
    pushButton_2->setSizePolicy(sizePolicy);
    pushButton_2->setBaseSize(QSize(75, 15));

    horizontalLayout_5->addWidget(pushButton_2);

    pushButton_3 = new QPushButton(frame_7);
    pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
    sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
    pushButton_3->setSizePolicy(sizePolicy);
    pushButton_3->setBaseSize(QSize(75, 15));

    horizontalLayout_5->addWidget(pushButton_3);


    verticalLayout_2->addWidget(frame_7);

    verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_2->addItem(verticalSpacer);


    horizontalLayout_3->addWidget(frame_5);


    verticalLayout->addWidget(frame_3);

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
    sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
    tableView->setSizePolicy(sizePolicy);
    tableView->setMaximumSize(QSize(897979, 16777215));
    tableView->setBaseSize(QSize(280, 230));

    horizontalLayout_2->addWidget(tableView);


    verticalLayout->addWidget(Frame2);

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

    checkBox = new QCheckBox(Frame3);
    checkBox->setObjectName(QStringLiteral("checkBox"));

    horizontalLayout->addWidget(checkBox);


    verticalLayout->addWidget(Frame3);

    Frame4 = new QFrame(this);
    Frame4->setObjectName(QStringLiteral("Frame4"));
    sizePolicy1.setHeightForWidth(Frame4->sizePolicy().hasHeightForWidth());
    Frame4->setSizePolicy(sizePolicy1);
    Frame4->setFrameShape(QFrame::StyledPanel);
    Frame4->setFrameShadow(QFrame::Raised);
    verticalLayout_3 = new QVBoxLayout(Frame4);
    verticalLayout_3->setSpacing(0);
    verticalLayout_3->setContentsMargins(0,0,0,0);
    verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
    textBrowser = new QTextBrowser(Frame4);
    textBrowser->setObjectName(QStringLiteral("textBrowser"));
    sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
    textBrowser->setSizePolicy(sizePolicy1);
    textBrowser->setSizeIncrement(QSize(0, 0));
    textBrowser->setBaseSize(QSize(280, 90));
    textBrowser->setStyleSheet(QStringLiteral("border-color: rgb(255, 255, 255);"));

    verticalLayout_3->addWidget(textBrowser);


    verticalLayout->addWidget(Frame4);

    verticalLayout->setStretch(0, 1);
    verticalLayout->setStretch(1, 9);
    verticalLayout->setStretch(2, 1);
    verticalLayout->setStretch(3, 1);

    Icon->setText(QString());
    Title->setText(QApplication::translate("MainWindow", "Both My Dads Play Druids", 0));
    XOut->setText(QApplication::translate("MainWindow", "X", 0));
    pushButton_4->setText(QApplication::translate("MainWindow", "PushButton", 0));
    pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", 0));
    pushButton_3->setText(QApplication::translate("MainWindow", "PushButton", 0));
    label->setText(QApplication::translate("MainWindow", "Online Now: 1/3", 0));
    checkBox->setText(QApplication::translate("MainWindow", "CheckBox", 0));
    textBrowser->setPlaceholderText(QString());

    hide();
}
