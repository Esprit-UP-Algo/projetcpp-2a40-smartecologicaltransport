#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include<QPixmap>
#include<QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // Connection c;
  //  bool test=c.createconnection();
    MainWindow w;
   // if(test)
    //{
        //lkhadhra
        bckg b1(w);
        b1.style(0,0,1920,1080,"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:2, stop:0 #6ac963, stop:0.025 #4aa66a, stop:0.5 #0e7285);border-radius:40px;","");
        //lbidha lkbira
        bckg b2(w);
        b2.style(200,50,1700,900,"background-color:white;border-radius:40px;","");

        //boutons
        btn bouton1(w);
        bouton1.style(50,100,100,100,"QPushButton { background-image: url(:/new/prefix1/slim/slim/home s.png);}");
        btn bouton2(w);
        bouton2.style(50,250,100,100,"QPushButton { background-image: url(:/new/prefix1/slim/slim/managment s.png);}");
        btn bouton3(w);
        bouton3.style(50,400,100,100,"QPushButton { background-image: url(:/new/prefix1/slim/slim/map s.png);}");


    /*    bckg bigwidget(w);
        bigwidget.style(250,100,500,400,"background-color:white;border-radius:40px;");*/
        bckg widgetliste(w);
        widgetliste.style(350,200,800,500,"background-color:white;border-radius:40px;","<h2 style='color:black'>CRUD</h2>");
        bckg widgetstatics(w);
        widgetstatics.style(1250,200,500,500,"background-color:white;border-radius:40px;","<h2 style='color:black'>Statistiques</h2>");


        btn bouton_ajout(w,"Ajouter une station");
        bouton_ajout.style(900,600,150,50,"background-color: white;border-style: outset;border-width: 2px;border-radius: 10px;border-color: green;font: bold 14px;min-width: 10em;padding: 6px;");
        btn bouton_tri(w,"Trier");
        bouton_tri.style(400,250,100,50,"background-color: white;border-style: outset;border-width: 2px;border-radius: 10px;border-color: green;font: bold 14px;min-width: 10em;padding: 6px;");
        w.show();
     //   QMessageBox::information(nullptr,QObject::tr("database is open"),QObject::tr("connection successful.\n""Click Cancel to exit."),QMessageBox::Cancel);
    //}
 //   else
   //     QMessageBox::critical(nullptr,QObject::tr("database is not open"),QObject::tr("connection failed.\n""click cancel to exit."),QMessageBox::Cancel);

    return a.exec();
}

