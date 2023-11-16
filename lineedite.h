#ifndef LINEEDITE_H
#define LINEEDITE_H


#include"mainwindow.h"
class edite
{
public:
    QLineEdit *ed;


    QLabel *lab;
    edite();
    edite (QLabel *l,QRect pos);
    void set_text(QString);
    QString get_text(){return ed->text();}
    void donner_acces(){ed->setReadOnly(false);}
    void blocker_acces(){ed->setReadOnly(true);}
    void vider(){ed->clear();}
};

#endif // LINEEDITE_H
