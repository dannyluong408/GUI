#include "guildframe.hpp"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

GuildFrame::GuildFrame(QWidget *parent)
    : QFrame(parent)
{
    setObjectName("guildFrame");
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    setGeometry(150,250,300,400);
    setStyleSheet("border: 1px solid black;");

    guild_name = new QLabel(this);
    guild_name->setText("Both My Dads Play Druids");
    guild_name->setStyleSheet("border: 1px solid black;");
    guild_name->setGeometry(40,0,245,15);
    guild_name->setAlignment(Qt::AlignCenter);

    x = new QPushButton(this);
    x->setText("X");
    x->setGeometry(285,0,15,15);
    connect(x,SIGNAL(clicked(bool)),this,SLOT(hide()));

    meme = new QLabel(this);
    QPixmap oldguy(":/ui/images/oldguy.ico");
    meme->setPixmap(oldguy.scaled(40,40,Qt::KeepAspectRatio));
    meme->setGeometry(0,0,40,40);

    info = new QPushButton(this);
    info->setText("Information");
    info->setGeometry(40,15,75,15);
    settings = new QPushButton(this);
    settings->setText("Settings");
    settings->setGeometry(115,15,75,15);
    add = new QPushButton(this);
    add->setText("Add Member");
    add->setGeometry(190,15,75,15);


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/guild.db");
    if (!db.open()){
        qDebug() << "Failed opening db!";
        QApplication::quit();
    }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("Guild");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Rank"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Zone"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Class"));

    QTableView *view = new QTableView(this);
    view->setGeometry(10,45,280,230);
    view->setModel(model);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->verticalHeader()->setVisible(false);
    view->horizontalHeader()->setMaximumSectionSize(280);
    view->setSortingEnabled(true);
    view->sortByColumn(0, Qt::AscendingOrder);
    //view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setColumnWidth(0,75);
    view->setColumnWidth(1,75);
    view->setColumnWidth(2,75);
//  view->verticalHeader()->setSectionResizeMode(QHeader::strecth;)
    view->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->setWordWrap(true);
    view->show();


    online = new QLabel(this);
    online->setGeometry(10,280,100,15);
    online->setText("Online Now: 1/3");

    showOffline = new QCheckBox(this);
    showOffline->setLayoutDirection(Qt::RightToLeft);
    showOffline->setText("Show offline members:");
    showOffline->setGeometry(150,280,140,15);

    gmotd = new QTextBrowser(this);
    gmotd->setGeometry(10,300,280,90);
    gmotd->setText("GMOTD: WELCOME TO BOTH MY DADS PLAY DRUIDS :^]");

    setVisible(false);
}


void GuildFrame::hide(){
    setVisible(false);
}
