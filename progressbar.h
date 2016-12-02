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

