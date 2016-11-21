#ifndef GUILDFRAME2_HPP
#define GUILDFRAME2_HPP


#pragma once

#include <QtWidgets>


class GuildFrame2 : public QFrame
{
    Q_OBJECT
    public:
        GuildFrame2(QWidget *parent);
    private:
        QVBoxLayout *verticalLayout;
        QFrame *frame_3;
        QHBoxLayout *horizontalLayout_3;
        QLabel *Icon;
        QFrame *frame_5;
        QVBoxLayout *verticalLayout_2;
        QFrame *frame_6;
        QHBoxLayout *horizontalLayout_4;
        QLabel *Title;
        QPushButton *XOut;
        QFrame *frame_7;
        QHBoxLayout *horizontalLayout_5;
        QPushButton *pushButton_4;
        QPushButton *pushButton_2;
        QPushButton *pushButton_3;
        QSpacerItem *verticalSpacer;
        QFrame *Frame2;
        QHBoxLayout *horizontalLayout_2;
        QTableView *tableView;
        QFrame *Frame3;
        QHBoxLayout *horizontalLayout;
        QLabel *label;
        QCheckBox *checkBox;
        QFrame *Frame4;
        QVBoxLayout *verticalLayout_3;
        QTextBrowser *textBrowser;

};

#endif // GUILDFRAME2_HPP
