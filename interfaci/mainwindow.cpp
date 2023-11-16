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
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

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
    ui->pp->hide();


     Paiement P;
     ui->tableView_2->setModel(P.afficherp());


       ui->ajoutpf->hide();
         ui->tableView_2->show();

     QHeaderView* headerView = ui->tableView_2->horizontalHeader();
       headerView->setSectionResizeMode(QHeaderView::Stretch);


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
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_2->model());

        if (model) {
            QString content;
            //header
            for (int col = 0; col < model->columnCount(); ++col) {
                content += model->headerData(col, Qt::Horizontal).toString() + "\t ";
            }
            content += "\n";
            // Iterate through the data in the model and add it to the content
            for (int row = 0; row < model->rowCount(); ++row) {
                for (int col = 0; col < model->columnCount(); ++col) {
                    content += model->data(model->index(row, col)).toString() + "\t";
                }
                content += "\n";
            }

            // Create a QTextDocument and set its content
            QTextDocument document;
            document.setPlainText(content);

            // Create a dialog to select the save location for the Word document
            QString fileName = QFileDialog::getSaveFileName(this, "Exporter en Word", "C:/Users/talel/Desktop/New folder/interfaci", "Fichiers Word (*.docx)");

            if (!fileName.isEmpty()) {
                // Create a QTextDocumentWriter to generate the Word document
                QTextDocumentWriter writer(fileName);
                writer.setFormat("docx");

                // Write the document to the Word file
                if (writer.write(&document)) {
                    // Display a message to the user to confirm successful export
                    QMessageBox::information(this, "Export Word", "Le document Word a été créé avec succès.");
                } else {
                    // Display an error message if the export fails
                    QMessageBox::critical(this, "Export Word", "Erreur lors de la création du document Word.");
                }
            }
        }
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
