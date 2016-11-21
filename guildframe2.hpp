#ifndef GUILDFRAME2_HPP
#define GUILDFRAME2_HPP


#pragma once

#include <QtWidgets>


class GuildFrame2 : public QFrame
{
    Q_OBJECT
    public:
        GuildFrame2(QWidget *parent);
    public slots:
        void resizeMe(QSize newSize);

    private:
        QVBoxLayout *mainLayout;
        QFrame *Frame1;
        QHBoxLayout *horizontalLayout_3;
        QLabel *Icon;
        QFrame *subFrame1;
        QVBoxLayout *verticalLayout_2;
        QFrame *titleFrame;
        QHBoxLayout *horizontalLayout_4;
        QLabel *Title;
        QPushButton *XOut;
        QFrame *buttonFrame;
        QHBoxLayout *horizontalLayout_5;
        QPushButton *information;
        QPushButton *settings;
        QPushButton *addmember;
        QSpacerItem *verticalSpacer,*hSpacer;
        QFrame *Frame2;
        QHBoxLayout *horizontalLayout_2;
        QTableView *tableView;
        QFrame *Frame3;
        QHBoxLayout *horizontalLayout;
        QLabel *label;
        QCheckBox *showoffline;
        QFrame *Frame4;
        QVBoxLayout *verticalLayout_3;
        QTextBrowser *textBrowser;
};

#endif // GUILDFRAME2_HPP
