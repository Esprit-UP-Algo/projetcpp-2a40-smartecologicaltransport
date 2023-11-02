#ifndef TAXI_H
#define TAXI_H
#include <QString>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class taxi
{
private:
    QString immatricule,marque,modele,carburant,BoiteV,Statut,NumCH,TypeCO,Auton;
    int NBRPL,EtatCH;
public:
    //constructeurs
    taxi();
    taxi(QString,QString,QString,QString,int,QString,QString,QString,QString,int,QString);
    public:
        //Getteurs
        QString getMAT(){return immatricule;}
        QString getMarq(){return marque;}
        QString getMod(){return modele;}
        QString getCarb(){return carburant;}
        int     getNbrP(){return NBRPL;}
        QString getBV(){return BoiteV;}
        QString     getSta(){return Statut;}
        QString getNumCha () {return NumCH ;}
        QString getConn (){return TypeCO;}
        int  getEtatCH () {return EtatCH;}
        QString  getAuto(){return  Auton;}
        //Setteurs
        void setMAT(QString im){ immatricule=im;}
        void setMarq(QString ma ){ marque=ma;}
        void setMod(QString mo){ modele=mo;}
        void setCarb(QString ca){ carburant= ca;}
        void setNbrP(int n){ NBRPL=n;}
        void setBV(QString BV){ BoiteV=BV;}
        void setSta(QString N ){ Statut=N;}
        void setNumCha (QString ch) { NumCH =ch ;}
        void setConn (QString co){ TypeCO=co;}
        void setEtatCH (int ETC) { EtatCH= ETC;}
        void setAuto(QString AUT ){  Auton =AUT;}
        //Fonctionnalités de Base relatives a l'entité Etudiant
        bool ajouter();
        bool supprimer (QString );
        QSqlQueryModel *afficher();
        QSqlQueryModel *pluscinquante();
        QSqlQueryModel *Recherher(QString);
        int GTNOT();
        int GTL();
        int GTO();
        bool update(QString,QString,QString,QString,int,QString,QString,QString,QString,int,QString);

};

#endif // TAXI_H
