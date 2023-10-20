#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include "ui_mainwindow.h"
int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase :: addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("SYSTEM");
    db.setPassword("1234");
    QApplication a(argc, argv);
    MainWindow w;
    QGraphicsDropShadowEffect *shadow[5];
    QPropertyAnimation *ESS1,*ESS,* Animation_1,* Animation_2,* Animation_3,* Animation_4, * Animation_5,* Animation_6,* Animation_7,* Animation_8;
    Ui :: MainWindow ui;
    ui.setupUi(&w);
    for(int i=0;i<5;i++)
    {
        shadow[i]=new QGraphicsDropShadowEffect;
        shadow[i]->setBlurRadius(50);
        shadow[i]->setColor(QColor("gris"));
        shadow[i]->setOffset(10,10);
    }
    ui.NOMP4->setText("Drdi");
    ui.IMMATP4->setText("588TU11");
    ui.PP4->setText("P");
    ui.NOMP3->setText("Souid");
    ui.IMMATP3->setText("538TU71");
    ui.PP3->setText("NP");
    ui.NOMP2->setText("Ladjimi");
    ui.IMMATP2->setText("538TU71");
    ui.PP2->setText("NP");
    ui.NOMP1->setText("Sassi");
    ui.IMMATP1->setText("548TU74");
    ui.PP1->setText("P");
    ui.nom4->setText("Mekni");
    ui.mat4->setText("140TUN4471");
    ui.nom3->setText("Sassi");
    ui.mat2_2->setText("190TUN7728");
    ui.nom2->setText("Derouiche");
    ui.mat2->setText("DG766LV");
    ui.nom1->setText("Nasri");
    ui.mat1->setText("129TUN95");
    ui.Nom->setText("2002");
    ui.aa->setText("2002");
    ui.mm->setText("04/");
    ui.jj->setText("30/");
    ui.Telephone->setText("54879576");
    ui.Adresse->setText("Tunis, La marsa,Rue Exellence");
    ui.Permis->setText("RF548SA");
    ui.Nom->setText("Slim");
    ui.lineEdit->setText("222");
    ui.lineEdit_2->setText("222");
    ui.lineEdit_3->setText("55");
    //Shadow des fenetres
    ui.label_5->setGraphicsEffect(shadow[0]);
    ui.label_6->setGraphicsEffect(shadow[1]);
    ui.label_7->setGraphicsEffect(shadow[2]);
    ui.label_8->setGraphicsEffect(shadow[3]);
    ui.label_9->setGraphicsEffect(shadow[4]);

    //Statistique
    QBarSet *set0 = new QBarSet("TAXI ACTIF");
    QBarSet *set1 = new QBarSet("TAXI INACTIF");
    * set0 <<40 <<100  ;
    * set1 <<70 <<100  ;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("TAXI");
    chart->setAnimationOptions(QChart:: SeriesAnimations);
    chart->resize(300,300);

    QStringList categories;
    categories << " Aujourd'hui" ;
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui.label_34);
    //Animation des boutons
    //ESS
    ESS = new QPropertyAnimation(ui.pushButton_15,"geometry");
    ESS->setDuration(2000);
    ESS->setStartValue(ui.pushButton_15->geometry());
    ESS->setEndValue(QRect(40,70,107,580));
    //BTN1
    Animation_1 = new QPropertyAnimation(ui.pushButton_6,"geometry");
    Animation_1->setDuration(2000);
    Animation_1->setStartValue(ui.pushButton_6->geometry());
    Animation_1->setEndValue(QRect(40,510,107,101));

    //BTN2
    Animation_2 = new QPropertyAnimation(ui.pushButton_7,"geometry");
    Animation_2->setDuration(2000);
    Animation_2->setStartValue(ui.pushButton_7->geometry());
    Animation_2->setEndValue(QRect(40,290,107,101));

    //BTN3
    Animation_3 = new QPropertyAnimation(ui.pushButton_8,"geometry");
    Animation_3->setDuration(2000);
    Animation_3->setStartValue(ui.pushButton_8->geometry());
    Animation_3->setEndValue(QRect(40,400,107,101));
    //BTN4
    Animation_4 = new QPropertyAnimation(ui.pushButton_9,"geometry");
    Animation_4->setDuration(2000);
    Animation_4->setStartValue(ui.pushButton_9->geometry());
    Animation_4->setEndValue(QRect(40,180,107,101));
    //BTN5
    Animation_5 = new QPropertyAnimation(ui.pushButton_6,"geometry");
    Animation_5->setDuration(2000);
    Animation_5->setEndValue(ui.pushButton_6->geometry());
    Animation_5->setStartValue(QRect(60,510,107,100));
    //BTN6
    Animation_6 = new QPropertyAnimation(ui.pushButton_7,"geometry");
    Animation_6->setDuration(2000);
    Animation_6->setEndValue(ui.pushButton_7->geometry());
    Animation_6->setStartValue(QRect(40,290,107,100));
    //BTN7
    Animation_7 = new QPropertyAnimation(ui.pushButton_8,"geometry");
    Animation_7->setDuration(2000);
    Animation_7->setEndValue(ui.pushButton_8->geometry());
    Animation_7->setStartValue(QRect(40,400,107,100));
    //BTN8
    Animation_8 = new QPropertyAnimation(ui.pushButton_9,"geometry");
    Animation_8->setDuration(2000);
    Animation_8->setEndValue(ui.pushButton_9->geometry());
    Animation_8->setStartValue(QRect(40,180,107,100));
    //ESS1
    ESS1 = new QPropertyAnimation(ui.pushButton_15,"geometry");
    ESS1->setDuration(2000);
    ESS1->setEndValue(ui.pushButton_15->geometry());
    ESS1->setStartValue(QRect(40,70,107,580));
    int i=0;
    QObject :: connect(ui.pushButton_10,&QPushButton :: clicked,[&]()
    {
        if(i==0){
            Animation_1->setStartValue(ui.pushButton_6->geometry());
            Animation_2->setStartValue(ui.pushButton_7->geometry());
            Animation_3->setStartValue(ui.pushButton_8->geometry());
            Animation_4->setStartValue(ui.pushButton_9->geometry());
            ESS->setStartValue(ui.pushButton_15->geometry());
            Animation_4->start();
            Animation_3->start();
            Animation_2->start();
            Animation_1->start();
            ESS->start();
            ui.pushButton_10->setText("TURN");
            i=1;
        }
        else
        {
            Animation_5->setStartValue(ui.pushButton_6->geometry());
            Animation_6->setStartValue(ui.pushButton_7->geometry());
            Animation_7->setStartValue(ui.pushButton_8->geometry());
            Animation_8->setStartValue(ui.pushButton_9->geometry());
            ESS1->setStartValue(ui.pushButton_15->geometry());
            Animation_5->start();
            Animation_6->start();
            Animation_7->start();
            Animation_8->start();
            ESS1->start();
            ui.pushButton_10->setText("GO");
            i=0;
        }

    });
    //Affichage
    w.show();
    return a.exec();
}
