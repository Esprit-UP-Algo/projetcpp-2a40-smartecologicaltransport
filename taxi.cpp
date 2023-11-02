#include "taxi.h"
#include<QString>

taxi :: taxi(QString immatricule ,QString marque ,QString modele ,QString carburant ,int NBRPL ,QString BoiteV ,QString Statut ,QString NumCH,QString TypeCO,int EtatCH ,QString Auton)
{
    this->immatricule=immatricule;
    this->marque=marque;
    this->modele=modele;
    this->carburant=carburant;
    this->NBRPL=NBRPL;
    this->BoiteV=BoiteV;
    this->Statut=Statut;
    this->NumCH=NumCH;
    this->TypeCO=TypeCO;
    this->EtatCH=EtatCH;
    this->Auton=Auton;
}
bool taxi ::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into taxis (immatricule , marque , modele , carburant , NBRPL , BoiteV  , statut , NumCH , TypeCO , EtatCH , Auton    ) values(:immatricule, :marque , :modele, :carburant , :NBRPL , :BoiteV, :statut , :NumCH , :TypeCO , :EtatCH , :Auton)");
    query.bindValue(":immatricule",immatricule);
    query.bindValue(":marque",marque);
    query.bindValue(":modele",modele);
    query.bindValue(":carburant",carburant);
    query.bindValue(":NBRPL",NBRPL);
    query.bindValue(":BoiteV",BoiteV);
    query.bindValue(":statut",Statut);
    query.bindValue(":NumCH",NumCH);
    query.bindValue(":TypeCO",TypeCO);
    query.bindValue(":EtatCH",EtatCH);
    query.bindValue(":Auton",Auton);
        return query.exec();
}
bool taxi :: supprimer ( QString  immatricule )
{
    QSqlQuery query;
    query.prepare("Delete from taxis where immatricule=:immatricule");
    query.bindValue(":immatricule",immatricule);
    return query.exec();
}
QSqlQueryModel *taxi::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from taxis");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Immatricule"));
    return model;
}
QSqlQueryModel *taxi::pluscinquante()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from taxis WHERE  EtatCH>70 AND statut = 'libre' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Immatricule"));
    return model;
}
QSqlQueryModel *taxi::Recherher(QString immatricule )
{
    QSqlQueryModel *model = new QSqlQueryModel();
       QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule = :imm");
       query.bindValue(":imm", immatricule);
       query.exec();

       model->setQuery(query);

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Immatricule"));

       return model;
}
bool taxi :: update(QString immatricule ,QString marque, QString modele , QString carburant , int NBRPL , QString BoiteV , QString Statut , QString NumCH, QString TypeCO , int EtatCH , QString Auton)
{
    QSqlQuery query;
    query.prepare("UPDATE  taxis  SET  marque =:marque , modele=:modele , carburant=:carburant , NBRPL=:NBRPL  , BoiteV=:BoiteV , Statut=:Statut ,NumCH=:NumCH, TypeCO=:TypeCO , EtatCH=:EtatCH , Auton=Auton  WHERE immatricule =:immatricule");
    query.bindValue(":immatricule",immatricule);
    query.bindValue(":marque",marque);
    query.bindValue(":modele",modele);
    query.bindValue(":carburant",carburant);
    query.bindValue(":NBRPL",NBRPL);
    query.bindValue(":BoiteV",BoiteV);
    query.bindValue(":Statut",Statut);
    query.bindValue(":NumCH",NumCH);
    query.bindValue(":TypeCO",TypeCO);
    query.bindValue(":EtatCH",EtatCH);
    query.bindValue(":Auton",Auton);
        return query.exec();
}
int taxi :: GTNOT()
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM TAXIS");

       query.exec();
       query.next();
           int count = query.value(0).toInt();
           return count;
}
int taxi :: GTL()
{
    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM TAXIS WHERE statut = 'libre'");
        query.exec();
                query.next();
            int count = query.value(0).toInt();
            return count;
}
int taxi :: GTO()
{
    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM TAXIS WHERE statut = 'occupe'");
        query.exec();
                query.next();
            int count = query.value(0).toInt();
            return count;
}
taxi::taxi()
{

}
