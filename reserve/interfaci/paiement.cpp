#include "paiement.h"
#include <QTableView>
#include <QHeaderView>
#include <QComboBox>
Paiement::Paiement()
{
CINP=0;PAI = " ";MONTANT=0;
}

bool Paiement::ajouterp()
    {
           QSqlQuery query;

           query.prepare("INSERT INTO PAIEMENT (CIN,PAI,MONTANT) "
                         "VALUES (:CIN, :PAI, :MONTANT)");

           query.bindValue(":CIN", CINP);
           query.bindValue(":PAI", PAI);
           query.bindValue(":MONTANT", MONTANT);



           return query.exec();
       }
QSqlQueryModel* Paiement::afficherp()
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT* FROM PAIEMENT");
         model->setHeaderData(0, Qt::Horizontal,QObject:: tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal,QObject:: tr("PAI"));
         model->setHeaderData(2, Qt::Horizontal,QObject:: tr("MONTANT"));



         // Create a table view
            QTableView* tableView = new QTableView;
            tableView->setModel(model);

            // Get the header view
            QHeaderView* headerView = tableView->horizontalHeader();
            headerView->setSectionResizeMode(QHeaderView::Stretch); // Optional: Adjust the section resize mode
    return model;
}
