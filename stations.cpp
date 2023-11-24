#include "stations.h"
#include "editablesqlquerymodel.h"
Stations::Stations()
{
    ref="";
    statut="";
    nbr_bornes=0;
    type_connect="";
    rue="";
    ville="";
    code_postal="";
    longitude=0;
    latitude=0;
}
Stations::Stations(QString REF,QString STATUT,int NBR_BORNES,QString TYPE_CONNECT,QString RUE,QString VILLE,QString CODE_POSTAL,double  LATITUDE,double LONGITUDE )
{
    ref=REF;
    statut=STATUT;
    nbr_bornes=NBR_BORNES;
    type_connect=TYPE_CONNECT;
    rue=RUE;
    ville=VILLE;
    code_postal=CODE_POSTAL;
    longitude=LONGITUDE;
    latitude=LATITUDE;
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
    query.prepare("insert into stations (ref,statut,nbr_bornes,type_connect,rue,ville,code_postal,latitude,longitude) values(:ref,:statut,:nbr_bornes,:type_connect,:rue,:ville,:code_postal,:latitude,:longitude)");
    query.bindValue(":ref",ref);
    query.bindValue(":statut",statut);
    query.bindValue(":nbr_bornes",nbr_bornes);
    query.bindValue(":type_connect",type_connect);
    query.bindValue(":rue",rue);
    query.bindValue(":ville",ville);
    query.bindValue(":code_postal",code_postal);
    query.bindValue(":longitude",longitude);
    query.bindValue(":latitude",latitude);
    return query.exec();
}
bool Stations :: supprimer ( QString  ref )
{
    QSqlQuery query;
    query.prepare("Delete from stations where ref=:ref");
    query.bindValue(":ref",ref);
    return query.exec();
}
EditableSqlQueryModel *Stations::afficher(const QList<int> &editableColumns,int row,QString ch)
{

    EditableSqlQueryModel* model = new EditableSqlQueryModel;
    model->setEditModeEnabled(true);
    model->setEditableColumns(editableColumns);
    model->setEditableRows(row);

    model->setQuery(ch);

    model->insertColumn(model->columnCount());
    model->setHeaderData(model->columnCount() - 1, Qt::Horizontal, "Editer");
    model->insertColumn(model->columnCount());
    model->setHeaderData(model->columnCount() - 1, Qt::Horizontal, "Supprimer");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref"));
    return model;
}

bool Stations :: update(int colonne,QString ref,QVariant nv)
{
    QString ch=nv.toString();
    int nb=nv.toInt();
    QSqlQuery query;
    int test1=1;
    if(colonne==1)
    {
      query.prepare("UPDATE  Stations  SET statut=:newstatut WHERE ref ="+ref+"");
        query.bindValue(":newstatut",ch);
    }
    else
    {
        if(colonne==2)
        {
            query.prepare("UPDATE  Stations  SET nbr_bornes=:newnbr_bornes WHERE ref ="+ref+"");
                query.bindValue(":newnbr_bornes",nb);
        }
        else
        {
            if(colonne==4)
            {
                query.prepare("UPDATE  Stations  SET type_connect=:newtype_connect WHERE ref ="+ref+"");
                query.bindValue(":newtype_connect",ch);
                QTextStream outputStream(stdout);
                outputStream<<"ch="<<ch<<endl;
                outputStream<<"ref="<<ref<<endl;

        int countad = 0;
        for (int i=0;i<ch.size();i++)
        {
            QChar c=ch[i];
            if (c == ",")
            {
                countad++;
            }
        }
        QString rue ="";
        QString ville ="";
        QString code_postal="";
        if(countad==2)
        {
            QStringList tokens = ch.split(",");
           rue =tokens[0];
            ville =tokens[1];
            code_postal =tokens[2];
            if(tokens[0]==""||tokens[1]==""||tokens[2]=="")
                countad=-1;
        }
        if(countad<2)
        {
            test1=0;
        }
        if(test1==1)
        {
            query.prepare("UPDATE  Stations  SET rue=:tokens0,ville=:tokens1,code_postal=:tokens2 WHERE ref ="+ref+"");
            query.bindValue(":tokens0",rue);
            query.bindValue(":tokens1",ville);
            query.bindValue(":tokens2",code_postal);
        }
}
       }
    }

    return query.exec();
}
