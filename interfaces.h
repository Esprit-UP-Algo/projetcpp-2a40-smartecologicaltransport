#ifndef INTERFACES_H
#define INTERFACES_H

#include"mainwindow.h"
class interfaces
{
public:
    QGraphicsDropShadowEffect *sh;
    QLabel *lab;
    QLabel*titre;
    QPixmap img;
    interfaces();
    interfaces(QMainWindow *w,QRect pos,QString style,QString t);
    interfaces(QLabel* l,QRect pos,QString style,QString t);
};
class S_interfaces
{
public:
    QLabel *lab;
    QPixmap img;
    S_interfaces();
    S_interfaces(QLabel* l,QRect pos,QString ch);
};

#endif // INTERFACES_H
