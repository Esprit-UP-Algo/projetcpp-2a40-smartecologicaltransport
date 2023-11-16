#include "interfaces.h"

interfaces :: interfaces()
{

}

interfaces :: interfaces(QMainWindow *w,QRect pos,QString style,QString t)
{
    lab=new QLabel(w);
    sh=new QGraphicsDropShadowEffect;
    titre=new QLabel(lab);
    lab->setGeometry(pos);
    lab->setStyleSheet(style);
    sh->setColor(QColor("gris"));
    sh->setBlurRadius(50);
    sh->setOffset(0,0);
    lab->setGraphicsEffect(sh);
    if(t[0]!='\0')
    {
        img.load(t);
        titre->setPixmap(img);
        titre->resize(img.size());
        titre->move((pos.width()-titre->width())/2,20);
    }
    else
    {
        delete titre;
        titre->setStyleSheet("background-color:transparent;");
    }
}
interfaces :: interfaces(QLabel *l,QRect pos,QString style,QString t)
{
    lab=new QLabel(l);
    sh=new QGraphicsDropShadowEffect;
    titre=new QLabel(lab);
    lab->setGeometry(pos);
    lab->setStyleSheet(style);
    sh->setColor(QColor("gris"));
    sh->setBlurRadius(50);
    sh->setOffset(0,0);
    lab->setGraphicsEffect(sh);
    if(t[0]!='\0')
    {
        img.load(t);
        titre->setPixmap(img);
        titre->resize(img.size());
        titre->move((pos.width()-titre->width())/2,20);
    }
    else
    {
        delete titre;
        titre->setStyleSheet("background-color:transparent;");
    }
}

S_interfaces :: S_interfaces()
{

}
S_interfaces :: S_interfaces(QLabel *l,QRect pos,QString ch)
{
    lab=new QLabel(l);
    img.load(ch);
    lab->resize(img.size());
    lab->move(pos.x(),pos.y());
    lab->setPixmap(img);
}
