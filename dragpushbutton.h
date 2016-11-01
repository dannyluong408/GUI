#ifndef DRAGPUSHBUTTON_H
#define DRAGPUSHBUTTON_H


#include <QtWidgets>
#include <QPushButton>

class QDragEnterEvent;
class QDropEvent;

class PushButton : public QPushButton
{
    Q_OBJECT

public:
    PushButton(QWidget *parent = 0);


public slots:
    void doThisClicked();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    QPoint dragStartPosition;
};

#endif // DRAGPUSHBUTTON_H
