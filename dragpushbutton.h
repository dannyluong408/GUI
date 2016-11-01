#ifndef DRAGPUSHBUTTON_H
#define DRAGPUSHBUTTON_H


#include <QtWidgets>


class QDragEnterEvent;
class QDropEvent;

class PushButton : public QPushButton
{
public:
    PushButton(QWidget *parent = 0);

public slots:
    void doThisClicked();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // DRAGPUSHBUTTON_H
