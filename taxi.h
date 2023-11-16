#ifndef TAXI_H
#define TAXI_H
#include <QString>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QLineEdit>
#include <QKeyEvent>
#include<QLabel>
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QPdfWriter>
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
        int Recherher2(QString);
        int GTNOT();
        int GTL();
        int GTO();
        QString recupererMarque(QString );
        QString recupererModele(QString );
        QString recupererCarburant(QString );
        int  recupererNBRPL(QString);
        QString recupererBoiteV(QString );
        QString recupererStatut(QString );
        QString recupererNUMCH(QString );
        QString recupererTYEPCO(QString);
        int recupererETATCH(QString );
        QString recupererAUTON(QString immatricule);
        void showLabelFor5Seconds(QLabel *label);
        QSqlQueryModel *afficherHISTO();
        void ANIMAT();
        int Recherher3(QString immatricule);
        QSqlQueryModel *Recherher0(QString immatricule );
        bool update(QString,QString,QString,QString,int,QString,QString,QString,QString,int,QString);
        void generatePdf(const QString &fileName);
        void ecrireDansFichier(const QString& immatriculation, const QString& tempsSuppression);
        void ecrireDansFichier1(const QString& immatriculation, const QString& tempsAjout);
        void ecrireDansFichier2(const QString& immatriculation, const QString& tempsDeMiseAjour);
};

#endif // TAXI_H
