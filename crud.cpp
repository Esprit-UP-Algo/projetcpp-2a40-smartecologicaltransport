#include "crud.h"
#include"connection.h"
#include<QSqlQueryModel>
#include<QPrinter>
#include<QTableView>
#include<QMessageBox>
#include"QMainWindow"
#include<QTextDocumentWriter>
#include<QTextDocument>
#include<QMessageBox>
#include <QFile>
#include <QTextStream>
Crud::Crud()
{

}
void Crud :: intialiser_titre()
{
    titre.resize(9);
    for(int i=0;i<9;i++)
    {

        titre[i]=new QLabel (lab_crud);
        titre[i]->setGeometry(i*120,0,120,50);
        titre[i]->setStyleSheet("font: 14pt 'MS Shell Dlg 2';");
    }
    titre[0]->setText("Reference");
    titre[1]->setText(" Date");
    titre[2]->setText("Time_D");
    titre[3]->setText("Time_F");
    titre[4]->setText("Tarif");
    titre[5]->setText("Adresse_D");
    titre[6]->setText("Adresse_F");
    titre[7]->setText("Methode_p");
}

Crud :: Crud(QLabel *lab,QRect pos)
{
    lab_crud=new QLabel(lab);
    lab_crud->setGeometry(pos);
    lab_crud->setStyleSheet("background-color:transparent;");
    nbr_l=0;
    nbr_ajout=0;
    nbr_mod=0;
    nbr_sup=0;
    y=500;
    s=1;
    intialiser_titre();
    req_select();
    s=0;
    afficher_tab();
}
int Crud :: recherche_tab(QString ref)
{
    int i=0;
    while(i<nbr_l && ref!=tab[i].reference.get_text())
    {
        i++;
    }
    return i;
}
void Crud :: ajouter_tab(Line_tab l)
{
    if(recherche_tab(l.reference.ed->text())==nbr_l)
    {
        nbr_l++;

        tab.resize(nbr_l);
        tab[nbr_l-1]=Line_tab(lab_crud,l.pos);
        tab[nbr_l-1].remplir(l);
        afficher_tab();
        l.vider();
        l.couvert();
        annimer();
        if(s==0)
        {
            nbr_ajout++;
            qDebug() << "nbr" <<nbr_ajout;
            tab_ajout.push_back(tab[nbr_l-1]);
        }
     }
    else
    {
        l.reference.lab->setStyleSheet("background-color:red");

    }
}
void Crud :: afficher_tab()
{
    for(int i=0;i<nbr_l;i++)
    {
        tab[i].afficher();
    }
}
void Crud :: deafficher_tab()
{
    for(int i=0;i<nbr_l;i++)
    {
        tab[i].couvert();
    }
}
void Crud :: annimer()
{
    QObject::connect(tab[nbr_l-1].sup.b, &QPushButton::clicked, [&]()
    {
        QPoint globalPos = QCursor::pos();
        int mouseY = globalPos.y();
        int indice=(mouseY-y)/50;
        qDebug () << "indice=" << indice;
        if(indice>=0 && indice<nbr_l)
        {
            nbr_sup++;
            tab_sup.push_back(tab[nbr_l-1]);
            suprimer_tab(indice);
        }
    });
    QObject::connect(tab[nbr_l-1].edit.b, &QPushButton::clicked, [&]()
    {
        QPoint globalPos = QCursor::pos();
        int mouseY = globalPos.y();
        int indice=(mouseY-y)/50;
        qDebug () << "indice=" << indice;
        if(indice>=0 && indice<nbr_l)
        {
            Line_tab l(lab_crud,tab[indice].pos);
            l.reference.set_text(tab[indice].reference.get_text());
            tab[indice].couvert();
            tab[indice]=l;
            tab[indice].afficher();
        }
    });
}
void Crud :: suprimer_tab(int indice)
{
    deafficher_tab();
    for(int i=indice;i<nbr_l-1;i++)
    {

        tab[i]=tab[i+1];
        tab[i].deplacer({0,50*(i+1),120,50});
    }
    nbr_l--;
    afficher_tab();
}
void Crud :: trie_tab()
{
   Line_tab l;
   QRect pos;
   int test;
   do
   {
       test=1;
       for(int i=0;i<nbr_l-1;i++)
       {
           qDebug () << tab[i].tarif.get_text().toInt();
           if(tab[i].tarif.get_text().toInt()>tab[i+1].tarif.get_text().toInt())
           {
               test=0;

               l=tab[i];
               tab[i]=tab[i+1];
               tab[i+1]=l;


               pos=tab[i].pos;
               tab[i].deplacer(tab[i+1].pos);
               tab[i+1].deplacer(pos);

           }
       }
   }
   while(test==0);
}
int Crud :: compter(QString ch)
{
    int nbr=0;
    for(int i=0;i<nbr_l;i++)
    {
        if(ch==tab[i].meth_pay.get_text())
        {
            nbr++;
        }
    }
    return nbr;
}
void Crud :: modifier(Line_tab line, int indice)
{
    tab[indice].couvert();
    tab[indice]=Line_tab(lab_crud,tab[indice].pos);
    tab[indice].remplir(line);
    tab_modifier.push_back(tab[indice]);
    nbr_mod++;
    afficher_tab();
}
Crud :: ~Crud()
{
    req_ajout();
    req_modifier();
    req_sup();
}


void Crud::req_modifier()
{
    for (int i = 0; i < nbr_mod; i++)
    {
        QSqlQuery query;  // Créez un nouvel objet QSqlQuery pour chaque opération

        query.prepare("UPDATE course SET DATE_C = TO_DATE(:date, 'YYYY-MM-DD'), HEURE_D = :heure_d, HEURE_F = :heure_f, TARIF = :tarif, ADRESSE_D = :adresse_d, ADRESS_F = :adresse_f, METHODE_P = :methode_p WHERE REFERENCES = :ref");
        QString dateText = tab_modifier[i].date->date().toString("yyyy-MM-dd");
                QString heureDText = tab_modifier[i].time_D->time().toString("HH:mm:ss");
                QString heureFText = tab_modifier[i].time_F->time().toString("HH:mm:ss");

                if (heureDText.length() > 20) {
                    heureDText = heureDText.left(20);
                }

                if (heureFText.length() > 20) {
                    heureFText = heureFText.left(20);
                }

        query.bindValue(":ref", tab_modifier[i].reference.get_text());
        query.bindValue(":date", dateText);
        query.bindValue(":heure_d", heureDText);
        query.bindValue(":heure_f", heureFText);
        query.bindValue(":tarif", tab_modifier[i].tarif.get_text());
        query.bindValue(":adresse_d", tab_modifier[i].adresse_D.get_text());
        query.bindValue(":adresse_f", tab_modifier[i].adresse_F.get_text());
        query.bindValue(":methode_p", tab_modifier[i].meth_pay.get_text());

        if (query.exec())
        {
            // Succès
        }
        else
        {
            qDebug() << "Échec : " << query.lastError().text();
        }
    }
}


void Crud :: req_sup()
{
    QSqlQuery query;

        for (int i = 0; i < nbr_sup; i++)
        {
            query.prepare("DELETE FROM course WHERE REFERENCES = :id");
            query.bindValue(":id", tab_sup[i].reference.get_text());


        }
        if (query.exec())
        {
            qDebug() << "non echec : " << query.lastError().text();
        }
        else
        {
            qDebug() << "nbr_sup=" << nbr_sup;
        }
}
void Crud :: req_ajout()
{
    QSqlQuery query;
    for (int i = 0; i < nbr_ajout; i++)
    {
        query.prepare("INSERT INTO course (REFERENCES, DATE_C, HEURE_D, HEURE_F, TARIF, ADRESSE_D, ADRESS_F, METHODE_P) "
                      "VALUES (:ref, TO_DATE(:date, 'YYYY-MM-DD'), :heure_d, :heure_f, :tarif, :adresse_d, :adresse_f, :methode_p)");

        QString dateText = tab_ajout[i].date->date().toString("yyyy-MM-dd");
        QString heureFText = tab_ajout[i].time_F->time().toString("HH:mm:ss");
        if (heureFText.length() > 20) {
            heureFText = heureFText.left(20); // Tronquer la chaîne à 20 caractères
        }
        query.bindValue(":ref", tab_ajout[i].reference.get_text());
        query.bindValue(":date", dateText);
        query.bindValue(":heure_d", tab_ajout[i].time_D->time().toString("HH:mm:ss"));
        query.bindValue(":heure_f", heureFText);
        query.bindValue(":tarif", tab_ajout[i].tarif.get_text());
        query.bindValue(":adresse_d", tab_ajout[i].adresse_D.get_text());
        query.bindValue(":adresse_f", tab_ajout[i].adresse_F.get_text());
        query.bindValue(":methode_p", tab_ajout[i].meth_pay.get_text());
    }
    if (query.exec())
    {
        qDebug() << "non echec : ";
    }
    else
    {
        qDebug() << "Échec de la suppression : " << query.lastError().text();
    }
}
void Crud :: req_select()
{
    Line_tab l(lab_crud,{0,50,120,50});
    QSqlQuery query;
    query.prepare("SELECT * FROM course");
    if (query.exec()) {
        while (query.next()) {
            l.reference.set_text(query.value(0).toString());
            l.date->setDate(QDate::fromString(query.value(1).toString(), "yyyy-MM-dd"));
            l.time_D->setTime(QTime::fromString(query.value(2).toString(), "hh:mm:ss"));
            l.time_F->setTime(QTime::fromString(query.value(3).toString(), "hh:mm:ss"));
            l.tarif.set_text(query.value(4).toString());
            l.adresse_D.set_text(query.value(5).toString());
            l.adresse_F.set_text(query.value(6).toString());
            l.meth_pay.set_text(query.value(7).toString());
            l.ajout.b->hide();
            l.edit.b->show();
            l.sup.b->show();
            l.blocker_acces();
            ajouter_tab(l);
            l.deplacer({0,50*(nbr_l+1),120,50});
        }
    } else {
        qDebug() << "Échec de la requête : " << query.lastError().text();
    }
}
void Crud::stat(QLabel* lab)
{
    QList<QWidget*> childWidgets = lab->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        lab->clear();
        lab->hide();

    float s0, s1;
    s0 = compter("enligne");
    s1 = compter("cache");

    float stat = s0 + s1;
    float x = (stat != 0) ? (s0 * 100) / stat : 0.0;
    float y = (stat != 0) ? (s1 * 100) / stat : 0.0;

    QString ch1 = QString("engline %1%").arg(x);
    QString ch2 = QString("cache %1%").arg(y);

        QPieSeries *series=new QPieSeries();
        series->setHoleSize(0.35);



        QPieSlice *slice= series->append(ch1,x);
        slice->setLabelVisible();
        slice->setLabelColor(QColor("0000000"));
            slice->setBrush(QColor(189, 76, 224, 1));
        QPieSlice *slice1= series->append(ch2,y);
        slice1->setLabelVisible();
        slice1->setLabelColor(QColor("0000000"));
        slice1->setBrush(QColor(84, 16, 149, 1));



        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QBrush backgroundBrush(QColor(187,93,87,0));
        chart->setBackgroundBrush(backgroundBrush);
        QChartView *chartview=new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setFixedSize(lab->size());
        chartview->setParent(lab);
        lab->setStyleSheet("background:transparent; color:white; ");
        lab->show();

}

void Crud::pdf(MainWindow* w)
{

    QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT* FROM course");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("REFERENCE"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("DATE_C"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("HEURE_D"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("HEUR_F"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("TARIF"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ADRESSE_D"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("ADRESSE_F"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("METHODE_P"));


             // Create a table view
                QTableView* tableView = new QTableView;
                tableView->setModel(model);

                // Get the header view
                QHeaderView* headerView = tableView->horizontalHeader();
                headerView->setSectionResizeMode(QHeaderView::Stretch);

    if (model) {
        QString content;
        //header
        for (int col = 0; col < model->columnCount(); ++col) {

             content += model->headerData(col, Qt::Horizontal).toString() + "\t ";

                }
        content += "\n";
        // Parcourez les données du modèle et ajoutez-les au contenu
        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                content += model->data(model->index(row, col)).toString() + "\t";
            }
            content += "\n";
        }

        // Créez un objet QTextDocument et définissez son contenu
        QTextDocument document;
        document.setPlainText(content);

        // Créez un dialogue pour sélectionner l'emplacement de sauvegarde du PDF.
        QString fileName = QFileDialog::getSaveFileName(w, "Exporter en PDF", "C:/Users/lenovo/pdf", "Fichiers PDF (*.pdf)");

        if (!fileName.isEmpty()) {
            // Créez un objet QPrinter pour générer le PDF.
            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);

            // Imprimez le document sur le PDF.
            document.print(&printer);

            // Affichez un message à l'utilisateur pour confirmer l'exportation réussie.
            //QMessageBox::information(this, "Export PDF", "Le PDF a été créé avec succès.");
        }
    }
}
void Crud::exel(MainWindow*w)
{
    QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT* FROM course");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("REFERENCE"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("DATE_C"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("HEURE_D"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("HEUR_F"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("TARIF"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ADRESSE_D"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("ADRESSE_F"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("METHODE_P"));


             // Create a table view
                QTableView* tableView = new QTableView;
                tableView->setModel(model);

        QString nomFile="fichier excel ";
                    QMessageBox msg;
                    if(!nomFile.length()){

                        msg.setText("entrer le nom du fichier");
                        msg.exec();
                    }
                    else{
                    QFile file("C:/Users/Poste1/Desktop/"+nomFile+".csv");
                    QString finalmsg="fichier modifie avec succes";
                     if(!file.exists()){
                     finalmsg="fichier cree avec succes";
                     }
                    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);

                    QTextStream txt(&file);
                    txt<<"id \t\t                  etat \t\t                        da \t\n";

                    for(int i=0;i<4;i++){

                        QString id = model->index(i, 0).data().toString();
                        QString etat = model->index(i, 1).data().toString();
                        QString da = model->index(i, 2).data().toString();




                    if(id.length()){

                    txt<< "'"+ id +"' \t";
                    txt<< "           '"+ etat +"' \t";
                    txt<< "             '"+ da +"' \t";

                    }
                    }
                    msg.setText(finalmsg);
                    msg.exec();
                    file.close();
                    }

}
