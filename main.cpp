#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    inter f(&w,{0,0,1930,990},"background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:2, stop:0.2 #6ac963 , stop:0.5 #4aa66a, stop:0.7 #0e7285);border-radius:60px;","");
    inter f2(&w,{160,50,1700,900},"background-color:white;border-radius:40px","");
    inter f_crud(&w,{300,200,1500,700},"background-color:white;border-radius:40px",":/new/titre/image/titre/gestion de conducteurs/Liste des conducteurs.png");
    btn_crud btn[5];
    for(int i=0;i<5;i++)
    {
        btn[i]=btn_crud(f_crud.lab,{150+i*250,50,220,50},"",":/new/crud/image/boutton_crud/"+QString :: number(i)+".png");
    }
    btn[0].b->setText("   ajout");
    btn[1].b->setText("   suprimer");
    btn[2].b->setText("    mise ajours");
    btn[3].b->setText("   filtrer");
    btn[4].b->setText("   recherche");

    w.show();
    return a.exec();
}
