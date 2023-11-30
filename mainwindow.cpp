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
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QApplication>
#include <QPainter>
#include <QTextDocument>
#include <QValidator>
#include <QPainter>
#include <QPdfWriter>
#include <QCoreApplication>
#include <QPdfWriter>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include<Windows.h>
#include<arduino.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
        ui->setupUi(this);

        int ret=A.connect_arduino();
        switch(ret)
        {
        case (0):qDebug()<<"arduino is avilble and connected to :"<<A.getArduino_port_name();
            break;
        case (1):qDebug()<<"arduino is avilble but not connected to :"<<A.getArduino_port_name();
            break;
        case (-1):qDebug()<<"arduino is not avilble ";
        }
        QObject::connect(A.get_serial(),SIGNAL(readyRead()),this,SLOT(update_ard()));

        //
        ui->groupBox_14->hide();
        ui->groupBox_10->hide();
        ui->groupBox_11->hide();
         ui->groupBox_12->hide();
         ui->groupBox_13->hide();
        ui->groupBox_9->hide();
        ui->tableView_5->setModel(T1.afficherHISTO());
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
    chart->resize(450,300);

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
    ui->label_12->setGraphicsEffect(sh[4]);
    ui->label_LISTE->setGraphicsEffect(sh[5]);
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->groupBox_5->hide();
    ui->groupBox_7->hide();
    //ui->label_38->hide();
    //ui->label_56->hide();
    //ui->label_57->hide();
    ui->groupBox_8->hide();
    //arduino


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
    QDoubleValidator validator ;
    QRegExp regex("^[A-Za-z0-9]{1,12}$");
    QRegExp regex2("^[A-Za-z0-9]{1,20}$");
    QString immatricule =ui->lineEdit_7->text();
    int A=T1.Recherher2(immatricule);
    if(A==0)
    {
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
             ui->checkBox_4->setChecked(false);
        }
        else if ( ui->checkBox_4->isChecked())
        {
             Statut="occupe";
             ui->checkBox_3->setChecked(true);
        }
        QString NumCH = ui->lineEdit_10->text();
        if(NumCH.contains(regex2))
        {
            QString TypeCO = ui->comboBox_4->currentText();
            int     EtatCH = ui->spinBox_2->text().toInt();
             QString Auton;
            if(ui->checkBox_5->isChecked())
            {
                ui->checkBox_6->setChecked(false);
                 Auton = "Autonome";

            }
            else if(ui->checkBox_6->isChecked())
            {
                ui->checkBox_5->setChecked(true);
                 Auton = "Non Autonome";
            }
            taxi  T(immatricule,marque,modele,carburant,NBRPL,BoiteV,Statut,NumCH,TypeCO,EtatCH,Auton);
            bool test=(T.ajouter());
            if (test)
            {
                QDateTime tempsActuel = QDateTime::currentDateTime(); // Récupérer le temps actuel
                   QString tempsAjout = tempsActuel.toString("dd/MM/yyyy hh:mm:ss"); // Formatage du temps
                   T1.ecrireDansFichier1(immatricule, tempsAjout);
                ui->lineEdit_7->setText("");
                 ui->spinBox=0;
                 ui->lineEdit_10->setText("");
                 ui->spinBox_2=0;
                // Refresh
                 ui->tableView_5->setModel(T1.afficherHISTO());
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
            QAbstractItemModel* model1 = ui->tableView_3->model();
            if (model1) {
                int rowCount = model1->rowCount();
                if (rowCount == 0 ) {
                    ui->pushButton->clicked();
                }
                else
                {
                    ui->groupBox_9->hide();
                }
            }
            }
            else
            ui->groupBox_13->hide();
        }
        else
            ui->groupBox_12->show();
        }
        else
            ui->groupBox_13->show();
    }
    else
        ui->groupBox_12->show();
    }
    else
        ui->groupBox_11->show();

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
    ui->groupBox_8->show();
}

void MainWindow::on_pushButton_27_clicked()
{
    QRegExp regex2("^[A-Za-z0-9]{1,12}$");
    QRegExp regex3("^[A-Za-z0-9]{1,20}$");
    QString immatricule =ui->Up->text();
    if(immatricule.contains("TUN",Qt::CaseInsensitive) &&  immatricule.contains(regex2))
    {
    int A=T1.Recherher2(immatricule);
    if(A==0)
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
                        QDateTime tempsActuel = QDateTime::currentDateTime(); // Récupérer le temps actuel
                           QString tempsDeMiseAjour = tempsActuel.toString("dd/MM/yyyy hh:mm:ss"); // Formatage du temps
                           T1.ecrireDansFichier2(immatricule, tempsDeMiseAjour);
                          //Vider Les cases
                        ui->Up->setText("");
                        ui->spinBox_5=0;
                        ui->lineEdit_15->setText("");
                        ui->spinBox_6=0;
                        // Refresh
                        ui->tableView_5->setModel(T1.afficherHISTO());
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
                    QAbstractItemModel* model1 = ui->tableView_3->model();
                    if (model1) {
                        int rowCount = model1->rowCount();
                        if (rowCount == 0 ) {
                            ui->pushButton->clicked();
                        }
                        else
                        {
                            ui->groupBox_9->hide();
                        }
                    }
                    else
                        ui->spinBox_5=0;
                        ui->lineEdit_15->setText("");
                        ui->spinBox_6=0;
                        ui->groupBox_5->hide();
        }
        else
            ui->groupBox_13->show();
    }
    else
        ui->groupBox_11->show();
    }
    ui->groupBox_10->show();

}

void MainWindow::on_pushButton_29_clicked()
{
    ui->groupBox_4->hide();
}

void MainWindow::on_pushButton_31_clicked()
{
    QString immatricule = ui->lineEdit_11->text();
    QRegExp regex("^[A-Za-z0-9]{1,12}$");
    if(immatricule.contains("TUN",Qt::CaseInsensitive) &&  immatricule.contains(regex) && T1.Recherher2(immatricule)==0)

    {
        bool test = (T1.supprimer(immatricule));
        if (test)
        {
            QDateTime tempsActuel = QDateTime::currentDateTime(); // Récupérer le temps actuel
               QString tempsSuppression = tempsActuel.toString("dd/MM/yyyy hh:mm:ss"); // Formatage du temps
               T1.ecrireDansFichier(immatricule, tempsSuppression);
            // Refresh
            ui->tableView_5->setModel(T1.afficherHISTO());
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
        //
        QAbstractItemModel* model1 = ui->tableView_3->model();
        if (model1) {
            int rowCount = model1->rowCount();
            if (rowCount == 0 ) {
                ui->pushButton->clicked();
            }
            else
            {
                ui->groupBox_9->hide();
            }
        }
    }
    else
    ui->groupBox_10->show();
}
    else
        ui->groupBox_10->show();
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
    int A=T1.Recherher2(imm);
    if (A==0)
    {
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
    else
        ui->groupBox_7->show();

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

void MainWindow::on_pushButton_37_clicked()
{
    QRegExp regex("^[A-Za-z0-9]{1,12}$");
    QString im=ui->lineEdit_14->text();
    int B=T1.Recherher2(im);
    if(im.contains(regex))
    {
    if(B=1)
    {
            ui->Up->setText(im);
        ui->groupBox_8->hide();
        ui->groupBox_5->show();
        //Getteurs
        QString M=T1.recupererMarque(im);
        QString Mo=T1.recupererModele(im );
        QString C=T1.recupererCarburant(im);
        int N=T1.recupererNBRPL(im);
        QString B=T1.recupererBoiteV(im);
        QString S=T1.recupererStatut(im);
        QString NCH=T1.recupererNUMCH(im);
        QString T=T1.recupererTYEPCO(im);
        int E=T1.recupererETATCH(im);
        QString A =T1.recupererAUTON(im);
        //Setteurs
        ui->comboBox_11->setCurrentText(M);
        ui->comboBox_12->setCurrentText(Mo);
        ui->comboBox_15->setCurrentText(C);
        ui->spinBox_5->setValue(N);
        ui->comboBox_13->setCurrentText(B);
        if(S=="libre")
        {
           ui->checkBox_11->setChecked(true);
           ui->checkBox_12->setChecked(false);
        }
        else
        {
            ui->checkBox_11->setChecked(false);
            ui->checkBox_12->setChecked(true);
        }
        ui->lineEdit_15->setText(NCH);
        ui->comboBox_14->setCurrentText(T);
        ui->spinBox_6->setValue(E);
        if(A=="Autonome");
        {
           ui->checkBox_13->setChecked(true);
           ui->checkBox_14->setChecked(false);
        }
        QAbstractItemModel* model1 = ui->tableView_3->model();
        if (model1) {
            int rowCount = model1->rowCount();
            if (rowCount == 0 ) {
                ui->pushButton->clicked();
            }
            else
            {
                ui->groupBox_9->hide();
            }
        }
    }
    }
    else
        ui->groupBox_10->show();
}

void MainWindow::on_pushButton_36_clicked()
{
   ui->groupBox_8->hide();
}

void MainWindow::on_pushButton_clicked()
{
    ui->groupBox_9->show();
    ESS = new QPropertyAnimation(ui->groupBox_9,"geometry");
    ESS->setDuration(3000);
    ESS->setStartValue(QRect(1440,1090,471,400));
    ESS->setEndValue(QRect(1440,560,471,400));
    ESS->start();
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->groupBox_9->hide();
}






void MainWindow::on_pushButton_3_clicked()
{
    ui->groupBox_10->hide();
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->groupBox_11->hide();
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->groupBox_12->hide();
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->groupBox_13->hide();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString imm=ui->lineEdit_2->text();
    int A=T1.Recherher3(imm);
    if (A==0)
    {
    QAbstractItemModel* model = ui->tableView_5->model();
    ui->lineEdit_2->setText("");
    if (model) {
        int rowCount = model->rowCount();
        if (rowCount == 0 ) {
          // ui->groupBox_7->show();
           ui->lineEdit_2->setText("");
        }
        else
        {
            //ui->groupBox_7->hide();
            ui->tableView_5->setModel(T1.Recherher0(imm));
            ui->lineEdit_2->setText("");
        }
    }
    }
    else
        ui->groupBox_7->show();

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->tableView_5->setModel(T1.afficherHISTO());
}

void MainWindow::on_pushButton_21_clicked()
{
    QString pdfFileName = "output.pdf";
       T1.generatePdf(pdfFileName);
       ui->groupBox_14->show();
}

void MainWindow::on_pushButton_38_clicked()
{
    ui->groupBox_14->hide();
}

void MainWindow::on_NOTIF_clicked()
{
    // Show a message box as a notification
    QMessageBox::information(this, "Notification", "Button pressed!");

    // Send a Windows notification
    NOTIFYICONDATA nid;
    ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = reinterpret_cast<HWND>(this->winId());
    nid.uID = 1;  // Unique ID for the notification icon
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;
    nid.uTimeout = 3000;  // Display time in milliseconds

    wcscpy_s(nid.szInfoTitle, L"Notification");
    wcscpy_s(nid.szInfo, L"Button pressed!");

    Shell_NotifyIcon(NIM_ADD, &nid);
    Shell_NotifyIcon(NIM_DELETE, &nid);
}
void MainWindow :: update_ard()
{
    QSqlQuery query;

        data=A.read_from_arduino();
        qDebug()<<"data="<<data;
        if(data=="0")
        {
            query.prepare("UPDATE  taxis  SET   Statut='libre'   WHERE immatricule ='129TUN95'");
            query.exec();

        }
        else
        {
            query.prepare("UPDATE  taxis  SET   Statut='occupe'   WHERE immatricule ='129TUN95'");
            query.exec();

        }

}
