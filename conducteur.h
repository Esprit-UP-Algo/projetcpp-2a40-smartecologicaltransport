#ifndef CONDUCTEUR_H
#define CONDUCTEUR_H
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Conducteur
{
public:
    Conducteur();
    Conducteur(int,QString,QString,int,QString,QDate);
    int getCIN();
    QString getPRENOM();
    QString getNOM();
    int getNUMTEL();
    QString getADRESSEMAIL();
    QDate getDATTE_D_EMBAUCHE();
    void setCIN(int);
    void setPRENOM(QString);
    void setNOM(QString);
    void setNUMTEL(int);
    void setADRESSEMAIL(QString);
    void setDATTE_D_EMBAUCHE(QDate);
    bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int);
   bool modifier(int,QString,QString,int,QString,QDate);
   bool idExists(int CIN);
   bool telExists(int NUMTEL);
   QSqlQueryModel* tri();
private:
    int CIN,NUMTEL;
    QString PRENOM, NOM, ADRESSEMAIL;
    QDate DATTE_D_EMBAUCHE;

};

#endif // CONDUCTEUR_H
