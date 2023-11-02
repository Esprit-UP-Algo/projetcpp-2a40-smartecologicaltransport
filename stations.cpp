#include "stations.h"

Stations::Stations()
{
    ref="";
    statut="";
    nbr_bornes=0;
    type_connect="";
    rue="";
    ville="";
    code_postal="";
}
Stations::Stations(QString REF,QString STATUT,int NBR_BORNES,QString TYPE_CONNECT,QString RUE,QString VILLE,QString CODE_POSTAL)
{
    ref=REF;
    statut=STATUT;
    nbr_bornes=NBR_BORNES;
    type_connect=TYPE_CONNECT;
    rue=RUE;
    ville=VILLE;
    code_postal=CODE_POSTAL;
}
QString Stations::get_ref(){return ref;}
QString Stations::get_statut(){return statut;}
int Stations::get_nbr_bornes(){return nbr_bornes;}
QString Stations::get_type_connect(){return type_connect;}
QString Stations::get_rue(){return rue;}
QString Stations::get_ville(){return ville;}
QString Stations::get_code_postal(){return code_postal;}

void Stations::set_ref(QString REF) {ref=REF;}
void Stations::set_statut(QString STATUT) {statut=STATUT;}
void Stations::set_nbr_bornes(int NBR_BORNES){nbr_bornes=NBR_BORNES;}
void Stations::set_type_connect(QString TYPE_CONNECT){type_connect=TYPE_CONNECT;}
void Stations::set_rue(QString RUE){rue=RUE;}
void Stations::set_ville(QString VILLE){ville=VILLE;}
void Stations::set_code_postal(QString CODE_POSTAL){code_postal=CODE_POSTAL;}

bool Stations::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into stations (ref,statut,nbr_bornes,type_connect,rue,ville,code_postal) values(:ref,:statut,:nbr_bornes,:type_connect,:rue,:ville,:code_postal)");
    query.bindValue(":ref",ref);
    query.bindValue(":statut",statut);
    query.bindValue(":nbr_bornes",nbr_bornes);
    query.bindValue(":type_connect",type_connect);
    query.bindValue(":rue",rue);
    query.bindValue(":ville",ville);
    query.bindValue(":code_postal",code_postal);
    return query.exec();
}
bool Stations :: supprimer ( QString  ref )
{
    QSqlQuery query;
    query.prepare("Delete from stations where ref=:ref");
    query.bindValue(":ref",ref);
    return query.exec();
}
QSqlQueryModel *Stations::afficher()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from Stations");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref"));
    return model;
}

bool Stations :: update()
{
    QSqlQuery query;
    query.prepare("UPDATE  Stations  SET statut=:statut,nbr_bornes=:nbr_bornes,type_connect=:type_connect,rue=:rue,ville=:ville,code_postal=:code_postal   WHERE ref ="+ref+"");
    query.bindValue(":statut",statut);
    query.bindValue(":nbr_bornes",nbr_bornes );
    query.bindValue(":type_connect",type_connect);
    query.bindValue(":rue",rue);
    query.bindValue(":ville",ville );
    query.bindValue(":code_postal",code_postal );
    return query.exec();
}
