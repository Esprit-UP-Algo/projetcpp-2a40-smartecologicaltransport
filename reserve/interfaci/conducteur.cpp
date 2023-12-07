#include "conducteur.h"
#include <QSqlQuery>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>
#include <QTextDocument>
#include <QMessageBox>
#include <QTextTable>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextCursor>
#include <QTextBlockFormat>
#include <QTextCharFormat>
#include <QTextTableCell>
#include <QTextDocumentWriter>
Conducteur::Conducteur()
{
CIN=0;PRENOM=" ";NOM=" ";NUMTEL=0;ADRESSEMAIL=" ";DATTE_D_EMBAUCHE=QDate::currentDate();
}

Conducteur::Conducteur(int CIN,QString PRENOM,QString NOM,int NUMTEL,QString ADRESSEMAIL,QDate DATTE_D_EMBAUCHE)
{this->CIN=CIN;this->PRENOM=PRENOM;this->NOM=NOM;this->NUMTEL=NUMTEL;this->ADRESSEMAIL=ADRESSEMAIL;this->DATTE_D_EMBAUCHE=DATTE_D_EMBAUCHE;}
int Conducteur::getCIN(){return CIN;}
QString Conducteur::getPRENOM(){return PRENOM;}
QString Conducteur::getNOM(){return NOM;}
int Conducteur::getNUMTEL(){return NUMTEL;}
QString Conducteur::getADRESSEMAIL(){return ADRESSEMAIL;}
QDate Conducteur::getDATTE_D_EMBAUCHE(){return DATTE_D_EMBAUCHE;}
void Conducteur::setCIN(int CIN){this->CIN=CIN;}
void Conducteur::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void Conducteur::setNOM(QString NOM){this->NOM=NOM;}
void Conducteur::setNUMTEL(int NUMTEL){this->NUMTEL=NUMTEL;}
void Conducteur::setADRESSEMAIL(QString ADRESSEMAIL){this->ADRESSEMAIL=ADRESSEMAIL;}
void Conducteur::setDATTE_D_EMBAUCHE(QDate DATTE_D_EMBAUCHE){this->DATTE_D_EMBAUCHE=DATTE_D_EMBAUCHE;}
bool Conducteur::ajouter()
    {
           QSqlQuery query;

           query.prepare("INSERT INTO CONDUCTEURS (CIN,PRENOM,NOM,NUMTEL,ADRESSEMAIL,DATTE_D_EMBAUCHE) "
                         "VALUES (:CIN, :PRENOM, :NOM, :NUMTEL, :ADRESSEMAIL, :DATTE_D_EMBAUCHE)");

           query.bindValue(":CIN", CIN);
           query.bindValue(":PRENOM", PRENOM);
           query.bindValue(":NOM", NOM);
           query.bindValue(":NUMTEL", NUMTEL);
           query.bindValue(":ADRESSEMAIL",ADRESSEMAIL);
           query.bindValue(":DATTE_D_EMBAUCHE",DATTE_D_EMBAUCHE);


           return query.exec();
       }
QSqlQueryModel* Conducteur::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT* FROM CONDUCTEURS");
         model->setHeaderData(0, Qt::Horizontal,QObject:: tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal,QObject:: tr("PRENOM"));
         model->setHeaderData(2, Qt::Horizontal,QObject:: tr("NOM"));
         model->setHeaderData(3, Qt::Horizontal,QObject:: tr("NUMTEL"));
         model->setHeaderData(4, Qt::Horizontal,QObject:: tr("ADRESSEMAIL"));
         model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DATTE_D_EMBAUCHE"));


         // Create a table view
            QTableView* tableView = new QTableView;
            tableView->setModel(model);

            // Get the header view
            QHeaderView* headerView = tableView->horizontalHeader();
            headerView->setSectionResizeMode(QHeaderView::Stretch); // Optional: Adjust the section resize mode
    return model;
}
QSqlQueryModel* Conducteur::affichert(int x)
{   QSqlQuery query;

    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT PRENOM,NOM,etat FROM CONDUCTEURS ");
         query.bindValue(":x",x);
         model->setHeaderData(0, Qt::Horizontal,QObject:: tr("PRENOM"));
         model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal,QObject:: tr("ETAT"));

         // Create a table view
            QTableView* tableView = new QTableView;
            tableView->setModel(model);

            // Get the header view
            QHeaderView* headerView = tableView->horizontalHeader();
            headerView->setSectionResizeMode(QHeaderView::Stretch); // Optional: Adjust the section resize mode

    return model;
}
bool Conducteur::supprimer(int CIN)
{QSqlQuery query;
 query.prepare("Delete FROM CONDUCTEURS where CIN=:CIN");
    query.bindValue(0,CIN);
 return query.exec();
}
bool Conducteur::modifier(int CIN,QString PRENOM,QString NOM,int NUMTEL,QString ADRESSEMAIL,QDate DATTE_D_EMBAUCHE)
{

    QSqlQuery query;


    query.prepare("UPDATE CONDUCTEURS SET PRENOM=:PRENOM,NOM=:NOM,NUMTEL=:NUMTEL,ADRESSEMAIL=:ADRESSEMAIL,DATTE_D_EMBAUCHE=:DATTE_D_EMBAUCHE where CIN=:CIN");

    query.bindValue(":CIN",CIN);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":NOM",NOM);
    query.bindValue(":NUMTEL",NUMTEL);
    query.bindValue(":ADRESSEMAIL",ADRESSEMAIL);
    query.bindValue(":DATTE_D_EMBAUCHE",DATTE_D_EMBAUCHE);



      /*if (query.exec()) {
          // Commit the transaction
          QSqlDatabase::database().commit();
          return true;
      } else {
          // Rollback the transaction in case of an error
          QSqlDatabase::database().rollback();
          return false;
      }*/
    return query.exec();


}
bool Conducteur::idExists(int CIN)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CONDUCTEURS WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

QSqlQueryModel* Conducteur::tri()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONDUCTEURS ORDER BY DATTE_D_EMBAUCHE ASC"); // Query modified to order by DATE_DE_DEBUT in ascending order
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal,QObject:: tr("NUMTEL"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("ADRESSEMAIL"));
    model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DATTE_D_EMBAUCHE"));
    // Create a table view
    QTableView* tableView = new QTableView;
    tableView->setModel(model);

    // Get the header view
    QHeaderView* headerView = tableView->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);

    return model;
}

bool Conducteur::telExists(int NUMTEL)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CONDUCTEURS WHERE NUMTEL = :NUMTEL");
    query.bindValue(":NUMTEL", NUMTEL);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}
