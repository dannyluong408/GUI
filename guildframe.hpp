#ifndef GUILDFRAME_HPP
#define GUILDFRAME_HPP

#pragma once

#include <QtWidgets>

class GuildFrame : public QFrame
{
    Q_OBJECT
    public:
        GuildFrame(QWidget *parent);
    public slots:
        void resizeMe(QSize size);
        void hide();

    private:
        QLabel *guildName,*online,*guildLogo;
        QPushButton *x,*info,*settings,*add;
        QTableView *guildTable;
        QCheckBox *showOffline;
        QTextBrowser *gmotd;
        QTableView *view;\
        QPixmap guildLogoPix;
};


#endif // GUILDFRAME_HPP
