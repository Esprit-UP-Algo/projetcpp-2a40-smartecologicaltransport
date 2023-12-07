#ifndef PAIEMENT_H
#define PAIEMENT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QComboBox>
class Paiement
{
public:
    Paiement();
    Paiement(int,QString,int);
    bool ajouterp();
   QSqlQueryModel* afficherp();
public:
   int CINP,MONTANT;

   QString PAI;
};

#endif // PAIEMENT_H
