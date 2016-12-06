#include "GUI/guildframe.hpp"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

GuildFrame::GuildFrame(QWidget *parent)
    : QFrame(parent)
{
    setObjectName("guildFrame");
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    setGeometry(200,200,300,400);
    setStyleSheet("border: 1px solid black;"
                  "background-color: white;");

    guildName = new QLabel(this);
    guildName->setText("Both My Dads Play Druids");
    guildName->setStyleSheet("border: 1px solid black;");
    guildName->setGeometry(40,0,245,15);
    guildName->setAlignment(Qt::AlignCenter);

    x = new QPushButton(this);
    x->setText("X");
    x->setGeometry(285,0,15,15);
    connect(x,SIGNAL(clicked(bool)),this,SLOT(hide()));

    guildLogo = new QLabel(this);
    guildLogoPix = QPixmap(":/ui/images/oldguy.ico");
    guildLogo->setPixmap(guildLogoPix.scaled(40,40,Qt::KeepAspectRatio));
    guildLogo->setGeometry(0,0,40,40);

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

    view = new QTableView(this);
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

void GuildFrame::resizeMe(QSize size){
    double scale_x = 300.0/1200.0;
    double scale_y = 400.0/900.0;

    double new_w = size.width();
    double new_h = size.height();

    //parent frame
    resize(new_w*scale_x,
           new_h*scale_y);


    //guild frame name
    scale_x = 40.0/1200.0;
    double scale_w = 245.0/1200.0;
    double scale_h = 15.0/900.0;


    guildName->setGeometry(new_w*scale_x,
                           0,
                           new_w*scale_w,
                           new_h*scale_h);

    //x
    scale_x = 285.0/1200.0;
    scale_w = 15.0/1200.0;
    scale_h = 15.0/900.0;

    x->setGeometry(new_w*scale_x,
                   0,
                   new_w*scale_w,
                   new_h*scale_h);

    //guildLogo
    scale_w = 40.0/1200.0;
    scale_h = 40.0/900.0;

    guildLogo->setGeometry(0,
                           0,
                           new_w*scale_w,
                           new_h*scale_h);
    guildLogo->setPixmap(guildLogoPix.scaled(new_w*scale_w,
                                             new_h*scale_h,
                                             Qt::KeepAspectRatio));

    //info
    scale_x = 40.0/1200.0;
    scale_y= 15.0/900.0;
    scale_w = 75.0/1200.0;
    scale_h = 15.0/900.0;

    info->setGeometry(new_w*scale_x,
                      new_h*scale_y,
                      new_w*scale_w,
                      new_h*scale_h);

    //settings
    scale_x = 115.0/1200.0;
    scale_y = 15.0/900.0;
    scale_w = 75.0/1200.0;
    scale_h = 15.0/900.0;

    settings->setGeometry(new_w*scale_x,
                          new_h*scale_y,
                          new_w*scale_w,
                          new_h*scale_h);
    //add
    scale_x = 190.0/1200.0;
    scale_y = 15.0/900.0;
    scale_w = 75.0/1200.0;
    scale_h = 15.0/900.0;

    add->setGeometry(new_w*scale_x,
                     new_h*scale_y,
                     new_w*scale_w,
                     new_h*scale_h);

    //tableview
    scale_x = 10.0/1200.0;
    scale_y = 45.0/900.0;
    scale_w = 280.0/1200.0;
    scale_h = 230.0/900.0;

    view->setGeometry(new_w*scale_x,
                      new_h*scale_y,
                      new_w*scale_w,
                      new_h*scale_h);

    //online
    scale_x = 10.0/1200.0;
    scale_y = 280.0/900.0;
    scale_w = 100.0/1200.0;
    scale_h = 15.0/900.0;

    online->setGeometry(new_w*scale_x,
                        new_h*scale_y,
                        new_w*scale_w,
                        new_h*scale_h);

    //offline
    scale_x = 150.0/1200.0;
    scale_y = 280.0/900.0;
    scale_w = 140.0/1200.0;
    scale_h = 15.0/900.0;

    showOffline->setGeometry(new_w*scale_x,
                             new_h*scale_y,
                             new_w*scale_w,
                             new_h*scale_h);

    //gmotd
    scale_x = 10.0/1200.0;
    scale_y = 300.0/900.0;
    scale_w = 280.0/1200.0;
    scale_h = 90.0/900.0;

    gmotd->setGeometry(new_w*scale_x,
                       new_h*scale_y,
                       new_w*scale_w,
                       new_h*scale_h);
    return;

}

void GuildFrame::hide(){
    setVisible(false);
}
