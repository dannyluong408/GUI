#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#pragma once

#include <QtWidgets>


class ProgressBar : public QProgressBar
{
    Q_OBJECT
    public:
        ProgressBar(QWidget *parent);

    public slots:
        void resizeMe(QSize newSize);

};


#endif // PROGRESSBAR_H
