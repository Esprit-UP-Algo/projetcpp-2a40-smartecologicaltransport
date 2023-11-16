#include "mainwindow.h"

#include <QApplication>
#include"interfaces.h"
#include"crud.h"
#include"connection.h"
int main(int argc, char *argv[])
{
    Connection cc;
    cc.createconnect();
    QApplication a(argc, argv);
    MainWindow w;
    interfaces inter(&w,{350,200,1500,700},"background-color:white;border-radius:50px;",":/new/prefix1/image/Liste des courses.png");
    Crud c(inter.lab,{200,200,1500,1000});
    bouttons ajout (inter.lab,{100,100,170,60},"background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.1 #6ac963, stop:0.4 #4aa66a, stop:0.6 #0e7285);color:white;","color:green;background-color:white;border:2px solid green","ajout");
    Line_tab l(c.lab_crud,{0,50,120,50});
    QLabel *lab=new QLabel(inter.lab);
    lab->setGeometry(1200,0,300,300);
    QObject :: connect(ajout.b,&QPushButton :: clicked,[&]
    {
        l.deplacer({0,50*(c.nbr_l+1),120,50});
        l.afficher();
    });
    QObject :: connect(l.ajout.b,&QPushButton :: clicked,[&]()
    {
        if(l.verifier())
        {
            c.ajouter_tab(l);
            c.stat(lab);
        }

     });
    edite e(inter.lab,{1000,100,170,60});
    e.ed->setPlaceholderText("Recherche");
    Line_tab l2(c.lab_crud,{0,50,120,50});
    QObject :: connect(e.ed,&QLineEdit :: textChanged,[&]()
    {
        int i=c.recherche_tab(e.get_text());

        if(i!=c.nbr_l)
        {
            c.deafficher_tab();
            l2.remplir(c.tab[i]);
            l2.afficher();
            e.lab->setStyleSheet("background-color:red;");
        }
        else
        {
            l2.couvert();
            c.afficher_tab();

        }
    });
    c.stat(lab);
     bouttons trie (inter.lab,{300,100,170,60},"background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.1 #6ac963, stop:0.4 #4aa66a, stop:0.6 #0e7285);color:white;","color:green;background-color:white;border:2px solid green","trie");
     QObject :: connect(trie.b,&QPushButton :: clicked,[&]()
     {
         c.trie_tab();
     });
     Line_tab modifier(c.lab_crud, {0,50,120,50});
     bouttons mod (inter.lab,{550,100,170,60},"background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.1 #6ac963, stop:0.4 #4aa66a, stop:0.6 #0e7285);color:white;","color:green;background-color:white;border:2px solid green","Modifier");
     QObject :: connect(mod.b,&QPushButton :: clicked,[&]()
     {
         modifier.deplacer({0,50*(c.nbr_l+1),120,50});
         modifier.afficher();
     });
     QObject :: connect(modifier.ajout.b,&QPushButton :: clicked,[&]()
     {
         int i=c.recherche_tab(modifier.reference.get_text());
         if(modifier.verifier() && i!=c.nbr_l)
         {
            c.modifier(modifier,i);
            modifier.couvert();
         }
         else if(i==c.nbr_l)
         {
             modifier.reference.lab->setStyleSheet("background-color:red;");
         }

      });
     bouttons b_pdf (inter.lab,{550,100,170,60},"background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.1 #6ac963, stop:0.4 #4aa66a, stop:0.6 #0e7285);color:white;","color:green;background-color:white;border:2px solid green","pdf");
     QObject :: connect(b_pdf.b,&QPushButton :: clicked,[&]()
     {
         c.pdf(&w);
     });
     bouttons exel (inter.lab,{100,500,170,60},"background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.1 #6ac963, stop:0.4 #4aa66a, stop:0.6 #0e7285);color:white;","color:green;background-color:white;border:2px solid green","exel");
     QObject :: connect(mod.b,&QPushButton :: clicked,[&]()
     {
         c.exel(&w);
     });
     w.show();
    return a.exec();
}
