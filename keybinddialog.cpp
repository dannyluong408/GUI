#include "keybindialog.hpp"

KeybindDialog::KeybindDialog(QWidget *parent)
    : QFrame(parent)
{
    setGeometry(150,150,150,150);
    setObjectName("keybindDialog");
    setStyleSheet("border: 2px solid black;"
                  "background-color: white;");
    info = new QLabel(this);
    info->resize(150,150);
    info->setText("Press a Key Combination! Press (ESC) to cancel!");
    info->setAlignment(Qt::AlignCenter);
    info->setWordWrap(true);
    num = -1;
    count = 0;
    grabKeyboard();
    show();
}

//possibly use QKeySequenceEdit in the future but probably not
void KeybindDialog::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Control || event->key() == Qt::Key_Control || event->key() == Qt::Key_Shift || event->key() == Qt::Key_Alt || event->key() == Qt::Key_unknown) {
        event->ignore();
        //qDebug() << "L:SKDFJK:SDF";
    }
    else if (event->key() == Qt::Key_Escape) {
        delete(this);
        return;
    }
    else {
        quint32 mod = event->modifiers();
        if (mod & Qt::ControlModifier ) keyPress.append("Ctrl+");
        if (mod & Qt::ShiftModifier ) keyPress.append("Shift+");
        if (mod & Qt::AltModifier ) keyPress.append("Alt+");
        keyPress.append(QKeySequence(event->key()).toString());
        qDebug() << keyPress;
        emit newBind(QKeySequence(keyPress), num);
        delete(this);
        return;
    }
}



