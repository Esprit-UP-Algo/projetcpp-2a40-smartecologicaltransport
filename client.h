#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQueryModel>
class Client
{
public:
    Client();

    Client(int cin) ;
  Client(QString ,QString ,QString ,int ,int );
    Client(QString,QString,int,QString,int,int);
    QString getnom();
    QString getprenom();
    int getCIN();
    QString getadresse();
    int getnum();
    int getpoint();

    void setnom(QString);
    void setprenom(QString);
    void setCIN(int);
    void setadresse(QString);
    void setnum(int);
    void setpoint(int);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
   bool cinexiste(int CIN);


   bool Modifier(QString nom,QString prenom,QString adresse,int num,int point);

private:
    int CIN;
    int num,point;
    QString nom,prenom,adresse;


};

#endif // CLIENT_H
