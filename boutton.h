#ifndef BOUTTONS_H
#define BOUTTONS_H

#include "mainwindow.h"
class bouttons
{
public:
    QPushButton *b;

    bouttons();
    bouttons(QLabel *l,QRect pos,QString enter,QString leave,QString text);
};
#endif // BOUTTON_H
