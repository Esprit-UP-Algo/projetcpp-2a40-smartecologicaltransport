#ifndef STATIONS_H
#define STATIONS_H
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
#include <QString>

#include "editablesqlquerymodel.h"
class Stations

{
    QString ref;
    QString statut;
    int nbr_bornes;
    QString type_connect;
    QString rue;
    QString ville;
    QString code_postal;
    double longitude;
    double latitude;
    public:
        Stations();
        Stations(QString,QString,int,QString,QString,QString,QString,double,double);

        QString get_ref();
        QString get_statut();
        int get_nbr_bornes();
        QString get_type_connect();
        QString get_rue();
        QString get_ville();
        QString get_code_postal();

        void set_ref(QString) ;
        void set_statut(QString);
        void set_nbr_bornes(int );
        void set_type_connect(QString );
        void set_rue(QString);
        void set_ville(QString);
        void set_code_postal(QString);

        bool ajouter();
        EditableSqlQueryModel* afficher(const QList<int> &editableColumns,int,QString);
        bool supprimer(QString);
        bool update(int colonne,QString ref,QVariant nv);

};

#endif // STATIONS_H
