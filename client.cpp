#include "client.h"
#include <QSqlQuery>
#include <QDebug>
#include<QtDebug>
#include <QObject>
Client::Client()
{
    CIN=0;
}
Client::Client(int CIN)
{
    this->CIN=CIN;
}
Client::Client(QString nom,QString prenom,QString adresse,int num,int point)
{
this->nom=nom; this->prenom=prenom; this->adresse=adresse; this->num=num; this->point=point;



}


Client::Client(QString nom,QString prenom, int CIN,QString adresse,int num,int point)
{
    this->nom=nom; this->prenom=prenom; this->CIN=CIN; this->adresse=adresse; this->num=num; this->point=point;

}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
int Client::getCIN(){return CIN;}
QString Client::getadresse(){return adresse;}
int Client::getnum(){return num;}
int Client::getpoint(){return point;}

void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setCIN(int CIN){this->CIN=CIN;}
void Client::setadresse(QString adresse){this->adresse=adresse;}
void Client::setnum(int num){this->num=num;}
void Client::setpoint(int point){this->point=point;}

bool Client::ajouter()
{
    QSqlQuery query;
    QString cin_string=QString::number(CIN);
    QString num_string=QString::number(num);
    QString point_string=QString::number(point);
          query.prepare("INSERT INTO CLIENT (CIN, NOM, PRENOM, ADRESSE_MAIL, NUM_TELEPHONE, POINT_DE_FIDELITE) "
                        "VALUES (:CIN, :NOM, :PRENOM, :ADRESSE_MAIL, :NUM_TELEPHONE, :POINT_DE_FIDELITE)");
          query.bindValue(0, cin_string);

          query.bindValue(1, nom);
          query.bindValue(2, prenom);
          query.bindValue(3, adresse);

          if (!adresse.contains('@') || !adresse.contains('.')) {
                      qDebug() << "Adresse email invalide : " << adresse;
                      return false;
                  }
          query.bindValue(4, num_string);
          query.bindValue(5, point_string);
          return query.exec();

}
bool Client::supprimer(int CIN)
{
    QSqlQuery query;
    query.prepare("DELETE from CLIENT where CIN=:CIN");
    query.bindValue(0, CIN);
    return query.exec();
}
QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM CLIENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_MAIL"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_TELEPHONE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("POINT_DE_FIDELITE"));

    return model;
}

bool Client ::cinexiste(int CIN)
{
    QSqlQuery query;
    query.prepare("SELECT CIN FROM CLIENT WHERE CIN=:CIN");
    query.bindValue(":CIN",CIN);
    if(query.exec()&&query.next())
    {
        return true;
}
    else
    {
        return false;

    }
}

 bool Client::Modifier(QString nom,QString prenom,QString adresse,int num,int point)
{


    QSqlQuery query;
    QString cin_string= QString::number(CIN);
    QString num_string=QString::number(num);
     QString point_string=QString::number(point);


          query.prepare("UPDATE CLIENT SET NOM= :NOM,PRENOM= :PRENOM,ADRESSE_MAIL= :ADRESSE_MAIL,NUM_TELEPHONE= :NUM_TELEPHONE,POINT_DE_FIDELITE= :POINT_DE_FIDELLITE WHERE CIN= :CIN;");

          query.bindValue("NOM", nom);
          query.bindValue("PRENOM", prenom);
          query.bindValue("ADRESSE_MAIL", adresse);
          query.bindValue("CIN", CIN);
          query.bindValue("NUM_TELEPHONE", num_string);
          query.bindValue("POINT_DE_FIDELITE", point_string);

          return query.exec();
}
