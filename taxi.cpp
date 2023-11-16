#include "taxi.h"
#include<QString>
#include <QLineEdit>
#include <QKeyEvent>
#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QPdfWriter>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QFileDialog>
#include <QtWidgets>
#include <QPdfWriter>
#include <QFile>
#include <QTextStream>
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
QSqlQueryModel *taxi::Recherher0(QString immatricule )
{
    QSqlQueryModel *model = new QSqlQueryModel();
       QSqlQuery query;
       query.prepare("SELECT * FROM  HISTO WHERE  immatricule = :immatricule");
       query.bindValue(":immatricule", immatricule);
       query.exec();

       model->setQuery(query);

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Immatricule"));

       return model;
}
int taxi::Recherher2(QString immatricule)
{
    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM TAXIS WHERE immatricule=:immatricule");
        query.exec();
                query.next();
            int count = query.value(0).toInt();
            return count;
}
int taxi::Recherher3(QString immatricule)
{
    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM HISTO WHERE immatricule=:immatricule");
        query.exec();
                query.next();
            int count = query.value(0).toInt();
            return count;
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
//RECUPERATION
QString taxi :: recupererMarque(QString immatricule )
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           QString marque = query.value("marque").toString();
           return marque;
}
}
QString taxi :: recupererModele(QString immatricule )
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           QString modele = query.value("modele").toString();
           return modele;
}
}
QString taxi :: recupererCarburant(QString immatricule)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           QString carburant = query.value("carburant").toString();
           return carburant;
}
}
int taxi :: recupererNBRPL(QString immatricule)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           int NBRPL = query.value("NBRPL").toInt();
           return NBRPL;
}
}
QString taxi :: recupererBoiteV(QString immatricule)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           QString B = query.value("BoiteV").toString();
           return B;
}
}
QString taxi :: recupererStatut(QString immatricule)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           QString B = query.value("Statut").toString();
           return B;
}
}
QString taxi :: recupererNUMCH(QString immatricule)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           QString B = query.value("NUMCH").toString();
           return B;
}
}
QString taxi :: recupererTYEPCO(QString immatricule)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           QString B = query.value("TypeCO").toString();
           return B;
}
}
int taxi :: recupererETATCH(QString immatricule)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           int NBRPL = query.value("EtatCH").toInt();
           return NBRPL;
}
}
QString taxi :: recupererAUTON(QString immatricule)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM taxis WHERE immatricule=:immatricule");
       query.bindValue(":immatricule", immatricule);

       if (query.exec() && query.next()) {
           QString B = query.value("Auton").toString();
           return B;
}
}
void taxi :: showLabelFor5Seconds(QLabel *label)
{
    label->show();

    QTimer *timer = new QTimer();
    timer->setSingleShot(true);
    QObject::connect(timer, &QTimer::timeout, label, &QLabel::hide);
    timer->start(5000); // Démarrer le timer pour masquer le QLabel après 5 secondes.
}
QSqlQueryModel *taxi::afficherHISTO()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("select * from HISTO");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Immatricule"));
    return model;
}
void taxi :: generatePdf(const QString &fileName)
{
    QSqlQuery query, query2;
        query.prepare("SELECT COUNT(*) FROM TAXIS WHERE statut = 'occupe'");
        query.exec();
                query.next();
            int count = query.value(0).toInt();
            //Les taxis libres
                query2.prepare("SELECT COUNT(*) FROM TAXIS WHERE statut = 'libre'");
                query2.exec();
                        query2.next();
                    int count1 = query2.value(0).toInt();
            QString myText = QString::number(count);
            QString myText1 = QString::number(count1);
    QPdfWriter pdfWriter(fileName);
    QPainter painter(&pdfWriter);

    // Set up the painter
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    //New Page
    painter.begin(&pdfWriter);
    // Start a new page
    QFont font;
    int fontSize = 25;  // Adjust the font size as needed
    font.setPointSize(fontSize);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.begin(&pdfWriter);

    // Ajouter une section d'en-tête
    painter.drawText(500, 900, "Rapport Instantané sur l'Activité des Taxis");

    painter.drawText(0,3800 , "Signature : Sassi Slim");
    painter.drawText(0, 4200, "Date de Création : " + QDate::currentDate().toString("dd/MM/yyyy"));
    painter.setPen(Qt::black);
    painter.drawText(2300, 2300, "Entreprise : GreenGO");
    painter.setPen(Qt::black); // Définir la couleur du stylo en noir
    painter.drawLine(0, 1100, pdfWriter.width(),1100);

    // Afficher les informations sur les taxis dans le PDF
    painter.setPen(Qt::red);
    painter.drawText(0, 2800, "Nombre de taxis occupés : " + myText);
    painter.drawText(0, 3200, "Nombre de taxis libres : " + myText1);
    painter.end();
}
void taxi ::ecrireDansFichier(const QString& immatriculation, const QString& tempsSuppression)
{
    QString nomFichier = "C:/Users/asus/OneDrive/Bureau/QT/build-final-Desktop_Qt_5_9_9_MinGW_32bit-Debug/HISTORIQUE.txt";
    QFile file(nomFichier);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream <<"SUPPRESSION:"<< "Immatriculation : " << immatriculation << ", Temps de suppression : " << tempsSuppression << "\n";
        file.close();
    } else {
        // Gérer les erreurs d'ouverture de fichier
    }
}
void taxi ::ecrireDansFichier1(const QString& immatriculation, const QString& tempsAjout)
{
    QString nomFichier = "C:/Users/asus/OneDrive/Bureau/QT/build-final-Desktop_Qt_5_9_9_MinGW_32bit-Debug/HISTORIQUE.txt";
    QFile file(nomFichier);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream <<"AJOUT :"<< "Immatriculation : " << immatriculation << ", Temps de l'ajout : " << tempsAjout << "\n";
        file.close();
    } else {
        // Gérer les erreurs d'ouverture de fichier
    }
}
void taxi ::ecrireDansFichier2(const QString& immatriculation, const QString& tempsDeMiseAjour)
{
    QString nomFichier = "C:/Users/asus/OneDrive/Bureau/QT/build-final-Desktop_Qt_5_9_9_MinGW_32bit-Debug/HISTORIQUE.txt";
    QFile file(nomFichier);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream <<"MISE A JOUR  :"<< "Immatriculation : " << immatriculation << ", Temps de l'ajout : " << tempsDeMiseAjour << "\n";
        file.close();
    } else {
        // Gérer les erreurs d'ouverture de fichier
    }
}
taxi::taxi()
{

}
