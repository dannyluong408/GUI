#pragma once

#include <QtWidgets>
#include <QPushButton>



class QDragEnterEvent;
class QDropEvent;

class PushButton : public QPushButton
{
    Q_OBJECT

public:
    PushButton(QWidget *parent = 0);
    uint32_t getSpellId();
    QIcon getIcon();
    void resizeMe(QSize newSize);
    void setSpellbookBool(bool value);
    void saveIcon(QPixmap origIcon);

public slots:
    void doThisClicked();
    void updateIcon(bool);
    void setSpellId(const uint32_t spellid);

signals:
    void spellPickedUp(const uint32_t spellid);
    void valueChanged(bool changed);

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QPoint dragStartPosition;
    uint32_t spell_id;
    QPixmap origIcon;
    bool spellbookIcon;
};

