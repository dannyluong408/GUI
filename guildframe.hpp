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
        void hide();

    private:
        QLabel *guild_name,*online,*meme;
        QPushButton *x,*info,*settings,*add;
        QTableView *guildTable;
        QCheckBox *showOffline;
        QTextBrowser *gmotd;
};


#endif // GUILDFRAME_HPP
