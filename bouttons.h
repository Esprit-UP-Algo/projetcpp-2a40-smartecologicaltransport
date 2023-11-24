#ifndef BOUTTONS_H
#define BOUTTONS_H
#include<QMainWindow>
#include <QLabel>
#include<QFrame>
#include<QPixmap>
#include <iostream>
#include <string>
#include<QFont>
#include <QGraphicsDropShadowEffect>
#include <QLineEdit>
#include<QPropertyAnimation>
#include<QPushButton>
#include<QCheckBox>
#include<QTimer>
class boutton : public QPushButton
{
public:
    QGraphicsDropShadowEffect *sh;
    QTimer t1,t2;
    int i;
    boutton();

    void annimer();
    boutton( QMainWindow *parent)
        : QPushButton( parent)
    {
        QFont font;

        font.setPointSize(14);
        setGeometry(877,869,170,60);
        setStyleSheet("QPushButton{background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.1 #6ac963, stop:0.4 #4aa66a, stop:0.6 #0e7285);border:none;color:white;font: 75 14pt 'MS Shell Dlg 2';border-radius:30px}");
        setText("Signe Up");
        setFont(font);
        sh=new QGraphicsDropShadowEffect;
        sh->setColor(QColor ("#0e7285"));
        sh->setOffset(0,0);
        sh->setBlurRadius(50);
        i=0;
        annimer();
    }
protected:
    void enterEvent(QEvent *) override
    {
        t1.start(5);
        t2.stop();
    }
    void leaveEvent(QEvent *)override
    {
        t2.start(5);
        t1.stop();
    }
};
class bouttons
{
public:
    QPushButton *b;
    bouttons();
    bouttons(QLabel *l,QRect pos,QString enter,QString leave,QString text);
};
class bouttons_img:public QPushButton
{
public:
    QLabel *lab;
    QPixmap img[2];
    bouttons_img();
    //bouttons_img(QLabel *l,QRect pos,QString enter,QString leave,QString text);
    bouttons_img( QLabel *parent,QRect pos,QString enter,QString leave)
        : QPushButton( parent)
    {
        lab=new QLabel(this);
        img[0].load(enter);
        img[1].load(leave);
        setGeometry(pos);
        lab->setGeometry(0,0,pos.width(),pos.height());
        lab->setPixmap(img[0]);
    }
protected:
    void enterEvent(QEvent *) override
    {
        lab->setPixmap(img[1]);
    }
    void leaveEvent(QEvent *)override
    {
        lab->setPixmap(img[0]);
    }
};
#endif // BOUTTONS_H
