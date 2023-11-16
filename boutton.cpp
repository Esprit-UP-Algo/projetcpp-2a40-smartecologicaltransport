#include "boutton.h"

bouttons::bouttons()
{

}
bouttons::bouttons(QLabel *l,QRect pos,QString enter,QString leave,QString text)
{
    QFont font;
    font.setPointSize(14);
    b=new QPushButton(l);
    b->setGeometry(pos);
    b->setStyleSheet("QPushButton {"+enter+"}"
                                           "QPushButton:hover{"+leave+"}");
    b->setFont(font);
    b->setText(text);

}
