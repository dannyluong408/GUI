#ifndef DRAGBUTTON_H
#define DRAGBUTTON_H

#include <QPushButton>
#include <QFrame>

class QDragEnterEvent;
class QDropEvent;

class DragButton : public QFrame
{
public:
    DragButton (QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};



#endif // DRAGBUTTON_H
