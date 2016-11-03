#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

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
