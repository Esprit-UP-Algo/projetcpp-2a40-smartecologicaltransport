#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsDropShadowEffect>
#include<QCoreApplication>
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include<taxi.h>
#include<string>
#include<iostream>
#include <QRegExp>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        ui->tableView_4->setModel(T1.afficher());
        ui->tableView_3->setModel(T1.pluscinquante());
        int A=T1.GTNOT();
        int B=T1.GTL();
        int C=T1.GTO();
        QString A1=QString::number(A);
        ui->lineEdit_5->setText(A1);
        QString B1=QString::number(B);
        ui->lineEdit_8->setText(B1);
        QString C1=QString::number(C);
        ui->lineEdit_9->setText(C1);
        QBarSet *set0 = new QBarSet("Taxi occupé");
    QBarSet *set1 = new QBarSet("TAXI Libre ");
    * set0 << C<<A ;
    * set1 << B<<A  ;

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
    chartView->setParent(ui->label_13);
    //ShadowEffect
    QGraphicsDropShadowEffect *sh[6];
    for(int i=0;i<6;i++)
    {
        sh[i]=new QGraphicsDropShadowEffect;
        sh[i]->setColor(QColor("black"));
        sh[i]->setBlurRadius(40);
        sh[i]->setOffset(0,0);
    }
    ui->label_8->setGraphicsEffect(sh[0]);
    ui->label_9->setGraphicsEffect(sh[1]);
    ui->label_10->setGraphicsEffect(sh[2]);
    ui->label_11->setGraphicsEffect(sh[3]);
    ui->label_12->setGraphicsEffect(sh[4]);
    ui->label_LISTE->setGraphicsEffect(sh[5]);
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->groupBox_5->hide();
    ui->groupBox_7->hide();
}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::on_pushButton_5_clicked()
{
    ui->groupBox->hide();
    ui->groupBox_2->show();
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->groupBox->show();
    ui->groupBox_2->hide();
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->groupBox_3->show();
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->groupBox_3->show();
}

void MainWindow::on_pushButton_22_clicked()
{
    QString immatricule =ui->lineEdit_7->text();
    QRegExp regex("^[A-Za-z0-9]{1,12}$");
    QRegExp regex2("^[A-Za-z0-9]{1,20}$");
    if(immatricule.contains("TUN",Qt::CaseInsensitive) &&  immatricule.contains(regex))
    {
        QString marque = ui->comboBox->currentText();
        QString modele = ui->comboBox_2->currentText();
        QString carburant = ui->comboBox_5->currentText();
        int     NBRPL = ui->spinBox->text().toInt();
        if(NBRPL<7)
        {
        QString BoiteV = ui->comboBox_3->currentText();
        QString Statut;
        if(ui->checkBox_3->isChecked())
        {
             Statut ="libre";
        }
        else if ( ui->checkBox_4->isChecked())
        {
             Statut="occupe";
        }
        QString NumCH = ui->lineEdit_10->text();
        if(NumCH.contains(regex2))
        {
            QString TypeCO = ui->comboBox_4->currentText();
            int     EtatCH = ui->spinBox_2->text().toInt();
             QString Auton;
            if(ui->checkBox_5->isChecked())
            {
                ui->checkBox_6->setCheckState(Qt::Unchecked);
                 Auton = "Autonome";

            }
            else if(ui->checkBox_6->isChecked())
            {
                ui->checkBox_5->setCheckState(Qt::Unchecked);
                 Auton = "Non Autonome";
            }
            taxi  T(immatricule,marque,modele,carburant,NBRPL,BoiteV,Statut,NumCH,TypeCO,EtatCH,Auton);
            bool test=(T.ajouter());
            if (test)
            {
                ui->lineEdit_7->setText("");
                 ui->spinBox=0;
                 ui->lineEdit_10->setText("");
                 ui->spinBox_2=0;
                // Refresh
                ui->tableView_4->setModel(T1.afficher());
                ui->tableView_3->setModel(T1.pluscinquante());
                ui->groupBox_3->hide();
                //STAT
                int A=T1.GTNOT();
                int B=T1.GTL();
                int C=T1.GTO();
                QString A1=QString::number(A);
                ui->lineEdit_5->setText(A1);
                QString B1=QString::number(B);
                ui->lineEdit_8->setText(B1);
                QString C1=QString::number(C);
                ui->lineEdit_9->setText(C1);
                QBarSet *set0 = new QBarSet("Taxi occupé");
            QBarSet *set1 = new QBarSet("TAXI Libre ");
            * set0 << C<<A ;
            * set1 << B<<A  ;
            ui->groupBox_7->hide();
            }
            else
            ui->groupBox_3->hide();
        }
        else
           ui->groupBox_7->show();
    }
    else
        ui->groupBox_7->show();
}
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->groupBox_3->show();
}
void MainWindow::on_pushButton_23_clicked()
{
    ui->groupBox_4->show();
}
void MainWindow::on_pushButton_17_clicked()
{
    ui->groupBox_5->show();
}

void MainWindow::on_pushButton_27_clicked()
{
    QString immatricule =ui->Up->text();
    QRegExp regex2("^[A-Za-z0-9]{1,12}$");
    QRegExp regex3("^[A-Za-z0-9]{1,20}$");

    if(immatricule.contains("TUN",Qt::CaseInsensitive) &&  immatricule.contains(regex2))
    {
        QString marque = ui->comboBox_11->currentText();
        QString modele = ui->comboBox_12->currentText();
        QString carburant = ui->comboBox_15->currentText();
        int     NBRPL = ui->spinBox_5->text().toInt();
        if(NBRPL<7)
        {
            QString BoiteV = ui->comboBox_13->currentText();
            QString Statut;
            if(ui->checkBox_11->isChecked())
            {
                 Statut ="libre";
            }
            else if ( ui->checkBox_12->isChecked())
            {
                 Statut="occupe";
            }
            QString NumCH = ui->lineEdit_15->text();
                if(NumCH.contains(regex3))
                {
                    QString TypeCO = ui->comboBox_14->currentText();
                    int     EtatCH = ui->spinBox_6->text().toInt();
                     QString Auton;
                    if(ui->checkBox_13->isChecked())
                    {
                         Auton = "Autonome";
                    }
                    else {
                         Auton = "Non Autonome";
                    }
                    bool test=(T1.update( immatricule,marque,modele,carburant,NBRPL,BoiteV,Statut,NumCH,TypeCO,EtatCH,Auton) && T2.update( immatricule,marque,modele,carburant,NBRPL,BoiteV,Statut,NumCH,TypeCO,EtatCH,Auton)) ;
                    if (test)
                    {
                        ui->Up->setText("");
                        ui->spinBox_5=0;
                        ui->lineEdit_15->setText("");
                        ui->spinBox_6=0;
                        // Refresh
                        ui->tableView_4->setModel(T1.afficher());
                        ui->tableView_3->setModel(T1.pluscinquante());
                        ui->groupBox_5->hide();
                        //STAT
                        int A=T1.GTNOT();
                        int B=T1.GTL();
                        int C=T1.GTO();
                        QString A1=QString::number(A);
                        ui->lineEdit_5->setText(A1);
                        QString B1=QString::number(B);
                        ui->lineEdit_8->setText(B1);
                        QString C1=QString::number(C);
                        ui->lineEdit_9->setText(C1);
                        QBarSet *set0 = new QBarSet("TAXI OCCUPE");
                    QBarSet *set1 = new QBarSet("TAXI LIBRE");
                    * set0 << B<<A ;
                    * set1 <<C <<A  ;
                    }
                    else
                        ui->Up->setText("");
                        ui->spinBox_5=0;
                        ui->lineEdit_15->setText("");
                        ui->spinBox_6=0;
                        ui->groupBox_5->hide();
                }
                else
                {
                    ui->groupBox_7->show();
                }
        }
        else {
            ui->groupBox_7->show();
        }
        }
    else {
        ui->groupBox_7->show();
    }
}
void MainWindow::on_pushButton_29_clicked()
{
    ui->groupBox_4->hide();
}

void MainWindow::on_pushButton_31_clicked()
{
    QString immatricule = ui->lineEdit_11->text();
    QRegExp regex("^[A-Za-z0-9]{1,12}$");
    if(immatricule.contains("TUN",Qt::CaseInsensitive) &&  immatricule.contains(regex))
    {
        bool test = (T1.supprimer(immatricule));
        if (test)
        {
            // Refresh
            ui->lineEdit_11->setText("");
            ui->tableView_4->setModel(T1.afficher());
            ui->tableView_3->setModel(T1.pluscinquante());
            ui->groupBox_4->hide();
            ui->lineEdit_11->setText("");
            //STAT
            int A=T1.GTNOT();
            int B=T1.GTL();
            int C=T1.GTO();
            QString A1=QString::number(A);
            ui->lineEdit_5->setText(A1);
            QString B1=QString::number(B);
            ui->lineEdit_8->setText(B1);
            QString C1=QString::number(C);
            ui->lineEdit_9->setText(C1);
            QBarSet *set0 = new QBarSet("TAXI OCCUPE");
        QBarSet *set1 = new QBarSet("TAXI LIBRE");
        * set0 << B<<A ;
        * set1 <<C <<A  ;
        ui->groupBox_4->hide();
        ui->groupBox_7->hide();
        }
    }
    else

    ui->groupBox_7->show();
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->groupBox_5->hide();
}

void MainWindow::on_pushButton_30_clicked()
{
    ui->groupBox_3->hide();
}

void MainWindow::on_pushButton_19_clicked()
{
    QString imm=ui->lineEdit_6->text();
    QAbstractItemModel* model = ui->tableView_4->model();
    ui->lineEdit_6->setText("");
    if (model) {
        int rowCount = model->rowCount();
        if (rowCount == 0 ) {
           ui->groupBox_7->show();
           ui->lineEdit_6->setText("");
        }
        else
        {
            ui->groupBox_7->hide();
            ui->tableView_4->setModel(T1.Recherher(imm));
            ui->lineEdit_6->setText("");
        }
    }

}

void MainWindow::on_pushButton_12_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_pushButton_13_clicked()
{
       ui->groupBox_2->hide();
       ui->groupBox->show();
}

void MainWindow::on_pushButton_2_clicked()
{
   ui->tableView_4->setModel(T1.afficher());
   ui->groupBox_7->hide();
}
