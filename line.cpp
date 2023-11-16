#include "line.h"

Line_tab::Line_tab()
{

}
Line_tab::~Line_tab()
{

}
Line_tab::Line_tab(QLabel *l,QRect p)
{
    for(int i=0;i<5;i++) test[i]=0;
    pos=p;
    line.resize(9);

    for(int i=0;i<9;i++)
    {
        line[i]=new QLabel (l);
        line[i]->setGeometry(pos.x()+i*pos.width(),pos.y(),pos.width(),pos.height());
        line[i]->setStyleSheet("background-color:transparent");
    }
    initialiser();
    style();
    controle_saisie();
    annimer();
    couvert();
}
void Line_tab :: initialiser()
{
    //reference=new QLineEdit(line[0]);
    reference=edite(line[0],{0,0,pos.width(),pos.height()});
    date=new QDateEdit (line[1]) ;
    time_D=new QTimeEdit(line[2]);
    time_F=new QTimeEdit(line[3]);
    tarif=edite(line[4],{0,0,pos.width(),pos.height()});
    adresse_D=edite(line[5],{0,0,pos.width(),pos.height()});
    adresse_F=edite(line[6],{0,0,pos.width(),pos.height()});
    meth_pay=edite(line[7],{0,0,pos.width(),pos.height()});
    ajout=bouttons(line[8],{0,0,pos.width(),pos.height()},"background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.1 #6ac963, stop:0.4 #4aa66a, stop:0.6 #0e7285);color:white;","color:green;background-color:white;border:2px solid green","ajout");
    edit=bouttons(line[8],{0,0,50,50},"background: url(:/new/prefix1/image/crayon (1).png)","background: url(:/new/prefix1/image/crayon.png)","");
    sup=bouttons(line[8],{50,0,50,50},"background: url(:/new/prefix1/image/supprimer-le-symbole (2).png)","background: url(:/new/prefix1/image/supprimer-le-symbole.png)","");
    edit.b->hide();
    sup.b->hide();
}
void Line_tab :: style()
{
    date->resize(line[0]->size());
    time_D->resize(line[0]->size());
    time_F->resize(line[0]->size());
}
void Line_tab:: blocker_acces()
{
    reference.blocker_acces();
    date->setReadOnly(true);
    time_D->setReadOnly(true);
    time_F->setReadOnly(true);
    tarif.blocker_acces();
    adresse_D.blocker_acces();
    adresse_F.blocker_acces();
    meth_pay.blocker_acces();
}
void Line_tab :: donner_acces()
{
    reference.donner_acces();
    date->setReadOnly(false);
    time_D->setReadOnly(false);
    time_F->setReadOnly(false);
    tarif.donner_acces();
    adresse_D.donner_acces();
    adresse_F.donner_acces();
    meth_pay.donner_acces();
}
void Line_tab ::deplacer(QRect p)
{
    pos=p;
    for(int i=0;i<9;i++)
    {
        line[i]->setGeometry(pos.x()+i*pos.width(),pos.y(),pos.width(),pos.height());
    }
}
void Line_tab :: vider()
{
    reference.vider();
    adresse_D.vider();
    adresse_F.vider();
    tarif.vider();
    meth_pay.vider();

}
void Line_tab :: controle_saisie()
{
    QDoubleValidator validator;
    reference.ed->setValidator(new QIntValidator(100,99999));
    tarif.ed->setValidator(new QIntValidator(100,99999));
    QObject :: connect(reference.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=reference.get_text();
        if(ch.length()>=4)
        {
            reference.lab->setStyleSheet("background-color:green");
            test[0]=1;
        }
        else
        {
            reference.lab->setStyleSheet("background-color:red");
            test[0]=0;
        }
    });

    QObject :: connect(tarif.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=tarif.get_text();
        if(ch.length()>=2)
        {
            tarif.lab->setStyleSheet("background-color:green");
            test[1]=1;
        }
        else
        {
            tarif.lab->setStyleSheet("background-color:red");
            test[1]=0;
        }
    });
    QObject :: connect(adresse_D.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=adresse_D.get_text();
        if(ch.length()>=2)
        {
            adresse_D.lab->setStyleSheet("background-color:green");
            test[2]=1;
        }
        else
        {
            adresse_D.lab->setStyleSheet("background-color:red");
            test[2]=0;
        }
    });
    QObject :: connect(adresse_F.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=adresse_F.get_text();
        if(ch.length()>=2)
        {
            adresse_F.lab->setStyleSheet("background-color:green");
            test[3]=1;
        }
        else
        {
            adresse_F.lab->setStyleSheet("background-color:red");
            test[3]=0;
        }
    });
    QObject :: connect(meth_pay.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=meth_pay.get_text();
        qDebug () <<"ch=" <<ch;
        if(ch=="enligne" || ch=="cache")
        {
            test[4]=1;
            meth_pay.lab->setStyleSheet("background-color:green;");
        }
        else
        {
            meth_pay.lab->setStyleSheet("background-color:red;");
            test[4]=0;
        }
    });
}
void Line_tab :: annimer()
{
    /*QObject :: connect(edit.b,&QPushButton:: clicked,[&]
    {
        Line_tab ll;
        ll.initialiser();
        ll.style();
        ll.controle_saisie();
    });*/

}
void Line_tab :: remplir(Line_tab l)
{
    reference.set_text(l.reference.ed->text());
    date->setDate(l.date->date());
    time_D->setTime(l.time_D->time());
    time_F->setTime(l.time_F->time());
    tarif.set_text(l.tarif.ed->text());
    adresse_D.set_text(l.adresse_D.ed->text());
    adresse_F.set_text(l.adresse_F.ed->text());
    meth_pay.set_text(l.meth_pay.ed->text());
    ajout.b->hide();
    edit.b->show();
    sup.b->show();

    blocker_acces();

}
void Line_tab :: afficher()
{
    for(int i=0;i<9;i++)
    {
        line[i]->show();
    }
}
void Line_tab :: couvert()
{
    for(int i=0;i<9;i++)
    {
        line[i]->hide();
    }
}
bool Line_tab :: verifier()
{
    int i=0;
    while(i<5 && test[i]!=0)
    {
        i++;
    }
    return i==5;
}
