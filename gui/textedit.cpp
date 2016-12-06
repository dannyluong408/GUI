#include "GUI/textedit.hpp"


TextEdit::TextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    setObjectName("chatInput");
}


void TextEdit::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
        case Qt::Key_Escape:{
            clear();
            hide();
            break;
        }
        case Qt::Key_Return:{
            emit send();
            break;
        }
        case Qt::Key_Enter:{
            emit send();
            break;
        }
        default:{
            QTextEdit::keyPressEvent(event);
        }
    }
}
