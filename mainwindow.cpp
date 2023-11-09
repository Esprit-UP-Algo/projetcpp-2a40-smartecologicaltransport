#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(100000, 99999999, this));
    ui->le_num->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_point->setValidator(new QIntValidator(0, 9999, this));
    ui->tab_client->setModel(c.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int CIN=ui->le_cin->text().toInt();
    QString adresse=ui->le_add->text();
    int num=ui->le_num->text().toInt();
    int point=ui->le_point->text().toInt();
    if (c.cinexiste(c.getCIN()))
    {
                 QMessageBox::critical(nullptr, QObject::tr("id"),
                    QObject::tr("ajout impossible:id existe deja  .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
    Client client(nom,prenom,CIN,adresse,num,point);
    bool test=client.ajouter();
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("Ajout avec succes.");
    ui->tab_client->setModel(client.afficher());}
    else
        msgBox.setText("Echec d'Ajout");
        msgBox.exec();
}

void MainWindow::on_pb_supp_clicked()
{
    Client C1;C1.setCIN(ui->le_cinsupp->text().toInt());
    bool test=C1.supprimer(C1.getCIN());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("Suppression avec succes.");
    ui->tab_client->setModel(c.afficher());
    }

    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();

}


void MainWindow::on_pushButton_clicked()
{
 ui->tab_client->setModel(c.afficher());;
}

void MainWindow::on_pb_ajouter_3_clicked()
{
    int CIN = ui->le_cin->text().toInt();

    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();

    QString adresse=ui->le_add->text();
    int point=ui->le_point->text().toInt();
     int num=ui->le_num->text().toInt();

Client c(CIN);
        if (c.cinexiste(CIN)) {

            bool test = c.Modifier(nom,prenom,adresse,num,point);

            if (test) {
                QMessageBox::information(nullptr, QObject::tr("MODIFICATION"),
                    QObject::tr("Modification réussie.\nClick Cancel to exit."), QMessageBox::Ok);

                ui->tab_client->setModel(c.afficher());
            } else {
                QMessageBox::critical(nullptr, QObject::tr("MODIFICATION"),
                    QObject::tr("Échec de la modification.\nClick Cancel to exit."), QMessageBox::Cancel);
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("MODIFICATION"),
                QObject::tr("Modification impossible : CIN inexistant.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }



