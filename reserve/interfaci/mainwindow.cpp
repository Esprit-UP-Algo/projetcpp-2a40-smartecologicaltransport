#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QFileDialog>
#include "conducteur.h"
#include <QTextDocument>
#include <QMessageBox>
#include <QTableView>
#include <paiement.h>
#include <QTextDocumentWriter>
#include<QtCharts>
#include <QScreen>
#include<QChartView>
#include<connection.h>
#include<QBarSet>
#include<QBarSeries>
#include <QFileDialog>
#include "arduino.h"
#include <QObject>
#include <QtSerialPort>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QLCDNumber>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
using namespace std;
#include<iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{  Connection c;
    bool test=c.createconnect();
    if(test)
    {
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

    ui->setupUi(this);
    ui->CIN->setValidator(new QIntValidator(100,99999999,this));
    ui->NUMTEL->setValidator(new QIntValidator(100,99999999,this));
    ui->MCIN->setValidator(new QIntValidator(100,99999999,this));
    ui->MNUMTEL->setValidator(new QIntValidator(100,99999999,this));
    QRegExp regex("[a-z]+", Qt::CaseInsensitive);
        QRegExpValidator* validator = new QRegExpValidator(regex, this);
        ui->PRENOM->setValidator(validator);
        ui->NOM->setValidator(validator);
        ui->MPRENOM->setValidator(validator);
        ui->MNOM->setValidator(validator);
    ui->conducteurs->hide();
    ui->ajouter->hide();
    ui->modif->hide();
    ui->tableView->hide();
    ui->gestion->show();
    ui->cc->hide();
    ui->mm->hide();
    ui->pp->hide(); ui->tableView_3->hide();

ref="";
     Paiement P;
     ui->tableView_2->setModel(P.afficherp());


       ui->ajoutpf->hide();
         ui->tableView_2->show();

     QHeaderView* headerView = ui->tableView_2->horizontalHeader();
       headerView->setSectionResizeMode(QHeaderView::Stretch);
       int ret=A.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

}
void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="D")
    {
        qDebug() << "ref=" << ref;
        changer_etat_travaille(ref,"travaille");

        ref.clear();
    }
    else if(!(data[0]=='\r' || data[0]=='\n'))
    {

        ref=ref+data[0];
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_editer_clicked()
{
    Conducteur C;
    ui->tableView->setModel(C.afficher());

    ui->gestion->hide();
      ui->ajouter->hide();
        ui->tableView->show();
    ui->conducteurs->show();
    QHeaderView* headerView = ui->tableView->horizontalHeader();
      headerView->setSectionResizeMode(QHeaderView::Stretch);


}
void MainWindow::on_return_2_clicked()
{
    ui->conducteurs->hide();
    ui->gestion->show();
    ui->ajouter->hide();
}
void MainWindow::on_pushButton_16_clicked()
{
     ui->tableView->hide();
    ui->ajouter->show();
}

void MainWindow::on_done_clicked()
{

 Conducteur C;
    int c=0;//nb  du faute dans controle saisie
        int CIN=ui->CIN->text().toInt();
        QString PRENOM=ui->PRENOM->text();
        QString NOM=ui->NOM->text();
        int NUMTEL=ui->NUMTEL->text().toInt();
         QString ADRESSEMAIL=ui->ADRESSEMAIL->text();
        QDate  DATTE_D_EMBAUCHE=ui->DATTE_D_EMBAUCHE->date();
        bool test2=C.idExists(CIN);

      if(test2)
         { c++;
                  QMessageBox::warning(nullptr, QObject::tr("CIN Invalide"), QObject::tr("CIN existe"), QMessageBox::Ok);
            }
      if(ui->CIN->text().isEmpty())
      { c++;
               QMessageBox::warning(nullptr, QObject::tr("CIN Invalide"), QObject::tr("Donner LE CIN "), QMessageBox::Ok);
         }
      bool test3=C.telExists(NUMTEL);

    if(test3)
       { c++;
                QMessageBox::warning(nullptr, QObject::tr("NUMTEL Invalide"), QObject::tr("NUMTEL existe"), QMessageBox::Ok);
          }
    if(ui->NUMTEL->text().isEmpty())
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("NUMTEL Invalide"), QObject::tr("Donner LE NUMTEL "), QMessageBox::Ok);
       }
    if(ui->NOM->text().isEmpty())
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("NOM Invalide"), QObject::tr("Donner LE NOM "), QMessageBox::Ok);
       }
    if(ui->PRENOM->text().isEmpty())
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("PRENOM Invalide"), QObject::tr("Donner LE PRENOM "), QMessageBox::Ok);
       }
    if(ui->ADRESSEMAIL->text().isEmpty())
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("ADRESSEMAIL Invalide"), QObject::tr("Donner LE ADRESSEMAIL "), QMessageBox::Ok);
       }
    QDate D=QDate::currentDate();
    if (DATTE_D_EMBAUCHE >D)
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("Date Invalide"), QObject::tr("Donner LE Date "), QMessageBox::Ok);
       }

        if(c==0) //si il n' y a pas problem dans le controle de saisie
            { Conducteur C(CIN,PRENOM,NOM,NUMTEL,ADRESSEMAIL,DATTE_D_EMBAUCHE);

            bool test=C.ajouter();
               QMessageBox msgBox;
               if(test)
                {msgBox.setText("Ajout avec succes.");
                      ui->tableView->setModel(C.afficher());

                      ui->ajouter->hide();
                      ui->tableView->show();
                      ui->CIN->clear();
                      ui->PRENOM->clear();
                      ui->NOM->clear();
                      ui->NUMTEL->clear();
                      ui->ADRESSEMAIL->clear();
                      ui->DATTE_D_EMBAUCHE->setDate(QDate());

                }
                else
                    msgBox.setText("echec d'ajout");
                msgBox.exec();


            }

}


void MainWindow::on_pushButton_17_clicked()
{
    QString id_string=ui->supprimer_text->text();
  int CIN=id_string.toInt();

Conducteur C;bool test,test1;
test=C.idExists(CIN);
if (test){
   test1 = C.supprimer(CIN);
}
          QMessageBox msgBox;
          if (test) {
              msgBox.setText("Suppression réussie.");
              ui->tableView->setModel(C.afficher());

          } else {
              msgBox.setText("Échec de la suppression.");

          }
          msgBox.exec();
}

void MainWindow::on_modifier_clicked()
{
   Conducteur C;
    int c=0;//nb  du faute dans controle saisie
        int CIN=ui->MCIN->text().toInt();
        QString PRENOM=ui->MPRENOM->text();
        QString NOM=ui->MNOM->text();
        int NUMTEL=ui->MNUMTEL->text().toInt();
         QString ADRESSEMAIL=ui->MADRESSEMAIL->text();
        QDate  DATTE_D_EMBAUCHE=ui->MDATTE_D_EMBAUCHE->date();



     /* if(ui->CIN->text().isEmpty())
      { c++;
               QMessageBox::warning(nullptr, QObject::tr("CIN Invalide"), QObject::tr("Donner LE CIN "), QMessageBox::Ok);
         }



    if(ui->NUMTEL->text().isEmpty())
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("NUMTEL Invalide"), QObject::tr("Donner LE NUMTEL "), QMessageBox::Ok);
       }
    if(ui->NOM->text().isEmpty())
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("NOM Invalide"), QObject::tr("Donner LE NOM "), QMessageBox::Ok);
       }
    if(ui->PRENOM->text().isEmpty())
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("PRENOM Invalide"), QObject::tr("Donner LE PRENOM "), QMessageBox::Ok);
       }
    if(ui->ADRESSEMAIL->text().isEmpty())
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("ADRESSEMAIL Invalide"), QObject::tr("Donner LE ADRESSEMAIL "), QMessageBox::Ok);
       }
    QDate D=QDate::currentDate();
    if (DATTE_D_EMBAUCHE >D)
    { c++;
             QMessageBox::warning(nullptr, QObject::tr("Date Invalide"), QObject::tr("Donner LE Date "), QMessageBox::Ok);
       }
*/
if (!C.idExists(CIN)){ QMessageBox::warning(nullptr, QObject::tr("OK"), QObject::tr("CIN non existante.\n""Click cancel to exit."), QMessageBox::Cancel);
     c++;   }   // Update the record in the database
if(c==0)
       {    bool test = C.modifier(CIN,PRENOM,NOM,NUMTEL,ADRESSEMAIL,DATTE_D_EMBAUCHE);
        if (test) {
               QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Modification successful.\n""Click cancel to exit."), QMessageBox::Cancel);

               ui->tableView->setModel(C.afficher()); // Refresh your table view after modification

               ui->MCIN->clear();
               ui->MPRENOM->clear();
               ui->MNOM->clear();
               ui->MNUMTEL->clear();
               ui->MADRESSEMAIL->clear();
               ui->MDATTE_D_EMBAUCHE->setDate(QDate());


           } else {
               QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Modification failed.\n""Click cancel to exit."), QMessageBox::Cancel);
           }
           ui->tableView->show();
            ui->modif->hide();
}}


void MainWindow::on_pushButton_18_clicked()
{
    ui->tableView->hide ();
    ui->modif->show();
}

void MainWindow::on_pushButton_20_clicked()
{
    int Conducteur=ui->recherche_text->text().toInt();


              QSqlQueryModel* searchModel = new QSqlQueryModel();
              QString conducteurString = QString::number(Conducteur);
              searchModel->setQuery("SELECT * FROM CONDUCTEURS WHERE CIN LIKE '%" + conducteurString + "%'");

              if (searchModel->rowCount() > 0) {
                  // If the search result is not empty
                  ui->tableView->setModel(searchModel);

                  // Adjust the header view as needed
                  QHeaderView* headerView = ui->tableView->horizontalHeader();
                  headerView->setSectionResizeMode(QHeaderView::Stretch);
              } else {
                  // If the search result is empty
                  QMessageBox::information(this, "Search Result", "cin does not exist.");
              }
}

void MainWindow::on_refrechini_clicked()
{
    Conducteur C;
    ui->tableView->setModel(C.afficher());
     ui-> recherche_text->clear();
}

void MainWindow::on_filtrini_clicked()
{
    Conducteur C;
    QSqlQueryModel* sortedModel =C.tri();

          // Assuming you have a member variable tableView of type QTableView in the MainWindow class
         ui->tableView->setModel(sortedModel);

          // Adjust the header view as needed
        QHeaderView* headerView = ui->tableView->horizontalHeader();
          headerView->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_pdf_clicked()
{
    // Associez le modèle à votre QTableView

        QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());

        if (model) {
            QString content;
            //header
            for (int col = 0; col < model->columnCount(); ++col) {

                 content += model->headerData(col, Qt::Horizontal).toString() + "\t ";

                    }
            content += "\n";
            // Parcourez les données du modèle et ajoutez-les au contenu
            for (int row = 0; row < model->rowCount(); ++row) {
                for (int col = 0; col < model->columnCount(); ++col) {
                    content += model->data(model->index(row, col)).toString() + "\t";
                }
                content += "\n";
            }

            // Créez un objet QTextDocument et définissez son contenu
            QTextDocument document;
            document.setPlainText(content);

            // Créez un dialogue pour sélectionner l'emplacement de sauvegarde du PDF.
            QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "file:///C:/Users/talel/Desktop/New folder/interfaci", "Fichiers PDF (*.pdf)");

            if (!fileName.isEmpty()) {
                // Créez un objet QPrinter pour générer le PDF.
                QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(fileName);

                // Imprimez le document sur le PDF.
                document.print(&printer);

                // Affichez un message à l'utilisateur pour confirmer l'exportation réussie.
                QMessageBox::information(this, "Export PDF", "Le PDF a été créé avec succès.");
            }
        }
}

void MainWindow::on_return_3_clicked()
{
    ui->modif->hide();
    ui->MCIN->clear();
    ui->MPRENOM->clear();
    ui->MNOM->clear();
    ui->MNUMTEL->clear();
    ui->MADRESSEMAIL->clear();
    ui->MDATTE_D_EMBAUCHE->setDate(QDate());
    ui->tableView->show ();
    ui->conducteurs->show();
}

void MainWindow::on_return_4_clicked()
{
    ui->ajouter->hide();
    ui->CIN->clear();
    ui->PRENOM->clear();
    ui->NOM->clear();
    ui->NUMTEL->clear();
    ui->ADRESSEMAIL->clear();
    ui->DATTE_D_EMBAUCHE->setDate(QDate());
    ui->tableView->show ();
    ui->conducteurs->show();
}

void MainWindow::on_pushButton_11_clicked()
{
    exportToPNG(ui->tableView_2);
}

void MainWindow::on_ajouterp_clicked()
{
    ui->ajouterp->hide();
    ui->tableView_2->hide();
    ui->cc->hide();
    ui->mm->hide();
    ui->pp->hide();
    ui->ajoutpf->show();
}

void MainWindow::on_confp_clicked()
{
    Paiement P;
    int c=0;//nb  du faute dans controle saisie
    P.CINP=ui->cinp->text().toInt();
    P.PAI=ui->pai->currentText();
    P.MONTANT = ui->mont->text().toInt();
    if(c==0) //si il n' y a pas problem dans le controle de saisie
     {
        bool test=P.ajouterp();
         QMessageBox msgBox;
               if(test)
                {msgBox.setText("Ajout avec succes.");
                      ui->tableView->setModel(P.afficherp());

                      ui->ajoutpf->hide();
                      ui->ajouterp->show();
                      ui->tableView_2->show();
                      ui->cinp->clear();
                      ui->mont->clear();
                      ui->pai->clear();


                }
                else
                    msgBox.setText("echec d'ajout");
                msgBox.exec();


            }

}




void MainWindow::on_show_clicked()
{
    Paiement P;
    ui->tableView_2->setModel(P.afficherp());

    ui->cc->show();
    ui->mm->show();
    ui->pp->show();
      ui->ajoutpf->hide();
        ui->tableView_2->show();

    QHeaderView* headerView = ui->tableView_2->horizontalHeader();
      headerView->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_pushButton_8_clicked()
{
    QList<QWidget*> childWidgets = ui->label_20->findChildren<QWidget*>();
            for (QWidget* childWidget : childWidgets) {
                childWidget->deleteLater();

            }
            //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
            ui->label_20->clear();
            ui->label_20->hide();

        float s0, s1;
        s0 = count0();
        s1 = count1();


        float stat = s0 + s1;
        float x = (stat != 0) ? (s0 * 100) / stat : 0.0;
        float y = (stat != 0) ? (s1 * 100) / stat : 0.0;


        QString ch1 = QString("service0:%1%").arg(x);
        QString ch2 = QString("service1:%1%").arg(y);


            QPieSeries *series=new QPieSeries();
            series->setHoleSize(0.35);



            QPieSlice *slice= series->append(ch1,x);
            slice->setLabelVisible();
            slice->setLabelColor(QColor(Qt::black));
            slice->setBrush(QColor(189, 76, 224, 1));
            QPieSlice *slice1= series->append(ch2,y);
            slice1->setLabelVisible();
            slice1->setLabelColor(QColor(Qt::black));
            slice1->setBrush(QColor(84, 16, 149, 1));
            QChart *chart=new QChart();
            chart->addSeries(series);
            chart->setAnimationOptions(QChart::SeriesAnimations);
            QBrush backgroundBrush(QColor(187,93,87,0));
            chart->setBackgroundBrush(backgroundBrush);
            QChartView *chartview=new QChartView(chart);
            chartview->setRenderHint(QPainter::Antialiasing);
            chartview->setFixedSize(ui->label_20->size());
            chartview->setParent(ui->label_20);
            ui->label_20->setStyleSheet("background:transparent; color:white; ");
            ui->label_20->show();
}
int MainWindow::count1()
{  int s = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(service) FROM conducteurs WHERE service= 1");

    if (query.exec()) {
        if (query.next()) {
            s = query.value(0).toInt();

            std::cout << "La valeur s5 est : " << s << std::endl;
        } else {
            std::cout << "Aucun enregistrement n'a été trouvé." << std::endl;
        }
    } else {
        std::cout << "Erreur lors de l'exécution de la requête." << std::endl;
    }

    return s;
}
int MainWindow::count0()
{  int s = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(service) FROM conducteurs WHERE service = 0");

    if (query.exec()) {
        if (query.next()) {
            s = query.value(0).toInt();

            std::cout << "La valeur s5 est : " << s << std::endl;
        } else {
            std::cout << "Aucun enregistrement n'a été trouvé." << std::endl;
        }
    } else {
        std::cout << "Erreur lors de l'exécution de la requête." << std::endl;
    }

    return s;
}
void MainWindow::exportToPNG(QTableView* tableView_2)
{
    // Take a screenshot of the table view
    QPixmap screenshot = tableView_2->grab();

    // Create a dialog to select the save location for the PNG image
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PNG", "C:/Users/talel/Desktop/New folder/interfaci", "Fichiers PNG (*.png)");

    if (!fileName.isEmpty()) {
        // Save the screenshot as a PNG file
        screenshot.save(fileName);

        // Display a message to the user to confirm successful export
        QMessageBox::information(this, "Export PNG", "L'image PNG a été créée avec succès.");
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

  if(date.day()==8 )
 {  Conducteur C;

      ui->tableView_3->setModel(C.affichert(4));
   ui->tableView_3->show();}


}
void MainWindow::changer_etat_travaille(QString REFERENCE,QString etat)
{

    QSqlQuery query;


    query.prepare("UPDATE CONDUCTEURS SET ETAT=:ETAT where REFERENCE=:REFERENCE");

    query.bindValue(":REFERENCE",ref);
    query.bindValue(":ETAT",etat);

    query.exec();

}
bool MainWindow::etat_travaille()
{
    QSqlQuery query;

    query.prepare("SELECT ETAT FROM CONDUCTEURS WHERE REFERENCE = :REFERENCE");
    query.bindValue(":REFERENCE",ref);

    if (query.exec() && query.next()) {
        QString etat = query.value(0).toString();
//qDebug()<<etat<<endl;
        if(etat=="travaille")
            return true;
        else
            return false;
    }


}


