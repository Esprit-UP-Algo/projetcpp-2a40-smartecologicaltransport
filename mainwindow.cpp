#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include "editablesqlquerymodel.h"
#include "mycustomdelegate.h"
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->groupBox_ajout->hide();
    ui->groupBox_supp->hide();
    ui->groupBox_modif1->hide();
    ui->groupBox_modif2->hide();
    ui->tableView_2->hide();
    ui->groupBox_recherche_introuvable->hide();
    ui->groupBox_gestion_station_1->show();


    QBarSet *set0 = new QBarSet("Ouvert");
    QBarSet *set1 = new QBarSet("Occupe ");
    QBarSet *set2 = new QBarSet("Hors Service ");
    QBarSet *set3 = new QBarSet("En construction ");
    * set0 << aa<<100 ;
    * set1 << bb<<100  ;
    * set2 << cc<<100  ;
    * set3 << dd<<100  ;
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statut des Stations");
    chart->setAnimationOptions(QChart:: SeriesAnimations);
    chart->resize(450,300);
    QStringList categories;
    categories << " Aujourd'hui" ;
    axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chartView = new QChartView(chart);
    chartView->setParent(ui->label_statistic);
   /* updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(stat()));
    updateTimer->start(5000);*/

        ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
        ui->quickWidget->show();

        connect(ui->tableView, &QTableView::clicked, this, &MainWindow::onTableViewClicked) ;

        int ret=A.connect_arduino(); // lancer la connexion à arduino

            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getArduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getArduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
            QObject::connect(A.get_serial(),SIGNAL(readyRead()),this,SLOT(reponse()));
               // permet de lancer
             //le slot update_label suite à la reception du signal readyRead (reception des données).
}
void MainWindow::reponse()
{
    pad=A.read_from_arduino();
    QString password = QString::fromUtf8(pad);
    if (!password.isEmpty() )
    {
        qDebug() << "Received password:" << password;
        QSqlQueryModel *model = new QSqlQueryModel();
        // Corrected SQL query
        QSqlQuery query;
        query.prepare("SELECT ref, statut, nbr_bornes, type_connect, (rue || ', ' || ville || ',' || code_postal) AS adresse FROM Stations WHERE ref = :password");
        query.bindValue(":password", password);
        query.exec();
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
        if (model->rowCount() > 0)
            A.write_to_arduino("1");
        else
            A.write_to_arduino("0");
    }
}
void MainWindow::on_pushButton_refresh_stat_clicked()
{
    int rowCount = tab.afficher(editableColumns,customDelegate->editrow,ch)->rowCount();
    for (int row = 1; row < rowCount; ++row)
    {
        QModelIndex index1 = tab.afficher(editableColumns,customDelegate->editrow,ch)->index(row, 1);
        QVariant data1 = tab.afficher(editableColumns,customDelegate->editrow,ch)->data(index1);
        if(data1.toString()=="Ouverte")
            {aa++;}
        else
        {
            if(data1.toString()=="Occupe")
                {bb++;}
            else
            {
                if(data1.toString()=="Hors service")
                {cc++;}
                else
                    {dd++;}
            }
        }
    }

        QBarSet *set0 = new QBarSet("Ouvert");
        QBarSet *set1 = new QBarSet("Occupe");
        QBarSet *set2 = new QBarSet("Hors Service");
        QBarSet *set3 = new QBarSet("En construction");

        *set0 << ((aa*100)/rowCount) << 100;
        *set1 << ((bb*100)/rowCount) << 100;
        *set2 << ((cc*100)/rowCount) << 100;
        *set3 << ((dd*100)/rowCount) << 100;

        QBarSeries *series = new QBarSeries();
        series->append(set0);
        series->append(set1);
        series->append(set2);
        series->append(set3);

        // Update the existing chart
        chart->removeAllSeries();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        // Refresh the chart view
        chartView->repaint();
}

/*
void MainWindow::onAddressClicked(const QModelIndex &index) {
    QString adresse = tab.afficher(editableColumns,customDelegate->editrow,ch)->data(index.sibling(index.row(), 4)).toString() ;

    // Assuming you have a QGeoCodeReply and QGeoCodingManager instance in your class
    QGeoCodeReply *reply = geoCodingManager->geocode(adresse);
    connect(reply, &QGeoCodeReply::finished, this, &MainWindow::onGeocodingFinished);
}*/
void MainWindow::handleNetworkReply(QNetworkReply *reply)
{
    QTextStream outputStream(stdout);
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

        if (!jsonResponse.isNull() && jsonResponse.isArray())
        {
            QJsonArray jsonArray = jsonResponse.array();

            if (!jsonArray.isEmpty())
            {
                QJsonObject locationObject = jsonArray.first().toObject();
                if (locationObject.contains("lat") && locationObject.contains("lon"))
                {
                    double latitude = locationObject["lat"].toDouble();
                    double longitude = locationObject["lon"].toDouble();

                    QString result = QString("Latitude: %1, Longitude: %2").arg(latitude).arg(longitude);


                    outputStream<<result<<endl;
                    // Set the location on the map
                    ui->quickWidget->rootObject()->setProperty("center", QVariant::fromValue(QGeoCoordinate(latitude, longitude)));
                }
                else
                {
                    outputStream<<"Invalid location format"<<endl;
                }
            }
            else
            {
                outputStream<<"No location found"<<endl;
            }
        }
        else
        {
            outputStream<<"Invalid JSON response"<<endl;
        }
    }
    else
    {
        outputStream<<"Error: " + reply->errorString()<<endl;
    }

    reply->deleteLater();
}

void MainWindow::onTableViewClicked(const QModelIndex &index)
{
    QString adresse = tab.afficher(editableColumns,customDelegate->editrow,ch)->data(index.sibling(index.row(), 4)).toString() ;
    QTextStream outputStream(stdout);
    outputStream<<adresse;
    int openParenIndex = adresse.indexOf("(");
   int closeParenIndex = adresse.indexOf(")");
   if (openParenIndex != -1 && closeParenIndex != -1) {
       // Extract the substring between parentheses
       QString coordinates = adresse.mid(openParenIndex + 1, closeParenIndex - openParenIndex - 1);

       // Split the substring into longitude and latitude
       QStringList parts = coordinates.split(',');

       if (parts.size() == 2) {
           // Extracted longitude and latitude as QString
           QString latitudeStr= parts[0].trimmed();
           QString longitudeStr  = parts[1].trimmed();

           // Convert QString to double
           bool ok1, ok2;
           double longitude = longitudeStr.toDouble(&ok1);
           double latitude = latitudeStr.toDouble(&ok2);
           if (ok1 && ok2) {
               // Convert longitude and latitude to QVariant
               QVariant longitudeVariant(longitude);
               QVariant latitudeVariant(latitude);
               /*auto Obje=ui->quickWidget->rootObject();
               connect(this,SIGNAL(setCenterPosition(QVariant,QVariant)),Obje,SLOT(setCenterPosition(QVariant,QVariant)));
            emit setCenterPosition( latitudeVariant,longitudeVariant);
               ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
               ui->quickWidget->show();*/
               QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "setCenterPosition",Q_ARG(QVariant, latitudeVariant),
                                             Q_ARG(QVariant, longitudeVariant));
           }
       }

    }
/*    QString apiKey = "EXu2fZwlNuThsWJQN49hpVZpnBhPgUSe";
            QString apiUrl = "http://www.mapquestapi.com/geocoding/v1/address?key=" + apiKey + "&location=" + adresse;


            QNetworkAccessManager *manager = new QNetworkAccessManager(this);
            connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::handleNetworkReply);

            QNetworkRequest request;
            request.setUrl(QUrl(apiUrl));

            manager->get(request);
    // Initialize the geocoding manager
        QGeoServiceProvider serviceProvider("osm");
        QGeoCodingManager *geocodingManager = serviceProvider.geocodingManager();

        // Start geocoding the address asynchronously
        QGeoCodeReply *reply = geocodingManager->geocode(adresse);

        // Connect the finished signal to handle the result
        connect(reply, &QGeoCodeReply::finished, this, [=]() {
            if (reply->error() == QGeoCodeReply::NoError) {
                // Retrieve the first result
                QList<QGeoLocation> locations = reply->locations();
                if (!locations.isEmpty()) {
                    QGeoLocation location = locations.first();

                    // Retrieve the coordinates
                    QGeoCoordinate coordinates = location.coordinate();

                    // Update the map's center to the selected address
                    QVariant lat = coordinates.latitude();
                    QVariant lon = coordinates.longitude();
                    ui->quickWidget->rootObject()->setProperty("center", QVariant::fromValue(QGeoCoordinate(lat.toDouble(), lon.toDouble())));
                } else {
                    // Handle the geocoding error
                    QMessageBox::warning(this, "Geocoding Error", "No locations found for the address.");
                }
            } else {
                // Handle the geocoding error
                QMessageBox::warning(this, "Geocoding Error", reply->errorString());
            }

            // Clean up the reply object
            reply->deleteLater();
        });*/

}
void MainWindow::updateMap(const QString &address, const QGeoCoordinate &coordinates)
{
    // Emit signal to update the map in QML
    emit addressClicked(address, coordinates);
}

MainWindow::~MainWindow()
{
    delete ui;
    A.get_serial()->close();
}

/*
void MainWindow::on_editButton_clicked(const QModelIndex& index)
{
    QModelIndex rowIndex = ui->tableView->currentIndex();
    if (rowIndex.isValid())
    {
        int row = rowIndex.row();
        // Récupérer les données de chaque colonne pour cette ligne
        QString ref = rowIndex.sibling(row, 0).data(Qt::EditRole).toString();
        QString statut = rowIndex.sibling(row, 1).data(Qt::EditRole).toString();
        int nbr_bornes = rowIndex.sibling(row, 2).data(Qt::EditRole).toInt();
        QString type_connect = rowIndex.sibling(row, 3).data(Qt::EditRole).toString();
        QString adresse = rowIndex.sibling(row, 4).data(Qt::EditRole).toString();
        QStringList tokens = adresse.split(",");
        QString rue =tokens[0];
        QString ville =tokens[1];
        QString code_postal =tokens[2];

        Stations S(ref,statut,nbr_bornes,type_connect,rue,ville,code_postal);
        bool test=S.update();
        if (test)
        {
            // Refresh
            ui->tableView->setModel(tab.afficher());
        }
    }
}
*/

void MainWindow::applyshadow()
{
    QGraphicsDropShadowEffect *shadow=new QGraphicsDropShadowEffect;
    shadow->setColor(QColor("gris"));
    shadow->setBlurRadius(50);
    shadow->setOffset(0,0);
    ui->graphicsView_bckg2->setGraphicsEffect(shadow);
    QGraphicsDropShadowEffect * shadow1=new QGraphicsDropShadowEffect;
    shadow1->setColor(QColor("gris"));
    shadow1->setBlurRadius(50);
    shadow1->setOffset(0,0);
    ui->graphicsView_crud->setGraphicsEffect(shadow1);
    QGraphicsDropShadowEffect * shadow2=new QGraphicsDropShadowEffect;
    shadow2->setColor(QColor("gris"));
    shadow2->setBlurRadius(50);
    shadow2->setOffset(0,0);
    ui->pushButton_ajout->setGraphicsEffect(shadow2);
    QGraphicsDropShadowEffect * shadow3=new QGraphicsDropShadowEffect;
    shadow3->setColor(QColor("gris"));
    shadow3->setBlurRadius(30);
    shadow3->setOffset(0,0);
    ui->lineEdit_recherche->setGraphicsEffect(shadow3);

    QGraphicsDropShadowEffect * shadow4=new QGraphicsDropShadowEffect;
    shadow4->setColor(QColor("gris"));
    shadow4->setBlurRadius(30);
    shadow4->setOffset(0,0);
    ui->graphicsView_bckg2_6->setGraphicsEffect(shadow4);

    QGraphicsDropShadowEffect * shadow5=new QGraphicsDropShadowEffect;
    shadow5->setColor(QColor("gris"));
    shadow5->setBlurRadius(30);
    shadow5->setOffset(0,0);
    ui->sendBtn->setGraphicsEffect(shadow5);


    QGraphicsDropShadowEffect * shadow6=new QGraphicsDropShadowEffect;
    shadow6->setColor(QColor("gris"));
    shadow6->setBlurRadius(30);
    shadow6->setOffset(0,0);
    ui->pushButton_exportation->setGraphicsEffect(shadow6);
}
void MainWindow::edit_mode()
{
    if(edit==false)
    {
        editableColumns={1,2,3,4,5,6};
         QTextStream outputStream(stdout);
         outputStream<<"row"<<customDelegate->editrow<<endl;
        edit=true;
        ui->tableView->setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
        liste1.setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
    }
    else
    {
        editableColumns={5,6};
        edit=false;
    }
    QTextStream outputStream(stdout);
    for (int i = 0; i < editableColumns.size(); ++i)
    {
            outputStream << editableColumns.at(i) << " ";
    }

}
void MainWindow::handle_delete()
{
    tab.supprimer(customDelegate->ref);
    ui->tableView->setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
    liste1.setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
}
void MainWindow::handle_update()
{
    tab.update(customDelegate->getEditColonne(),customDelegate->ref,customDelegate->getUpdatedValue());
    ui->tableView->setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
    liste1.setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
}
void MainWindow::TableWidgetDisplay()
{

   // customDelegate->setButtonColumn(5);
    //customDelegate->setOtherColumn(1);
    customDelegate->setView(ui->tableView);
    ui->tableView->setItemDelegate(customDelegate);
    editableColumns={5,6};
    ui->tableView->setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
    ui->tableView->setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
    connect(customDelegate, &MyCustomDelegate::buttonClicked,this, &MainWindow::edit_mode);

    QObject::connect(customDelegate, &MyCustomDelegate::dataChangedSignal,this, &MainWindow::handle_update);
    connect(customDelegate, &MyCustomDelegate::buttonsuppClicked,this, &MainWindow::handle_delete);



}


/*
void MainWindow::on_pushButton_management_clicked()
{

}
*/
void MainWindow::on_pushButton_ajout_clicked()
{
    ui->groupBox_ajout->show();
    ui->lineEdit_ref->setText("");
    ui->lineEdit_adresse->setText("");
    ui->lineEdit_adresse_2->setText("");
}
void MainWindow::on_pushButton_valide_ajout_clicked()
{
    int test1=1;
    QString ref =ui->lineEdit_ref->text();
    QString statut = ui->comboBox_statut->currentText();
    int nbr_bornes = ui->spinBox_nbr_bornes->text().toInt();
    QString type_connect = ui->comboBox_type_connect->currentText();
    QString adresse = ui->lineEdit_adresse->text();
    int countad = 0;
    for (int i=0;i<adresse.size();i++)
    {
        QChar c=adresse[i];
        if (c == ",")
        {
            countad++;
        }
    }
    QString adresse2 = ui->lineEdit_adresse_2->text();
    QStringList parts = adresse2.mid(1, adresse2.length() - 2).split(',');
    bool ok1=false;
    bool ok2=false;
    double value1;
    double value2;
    // Check if there are exactly two parts
    if (parts.size() == 2) {

         value1 = parts[0].toDouble(&ok1);
         value2 = parts[1].toDouble(&ok2);
    }
    QTextStream outputStream(stdout);
    outputStream<<value1<<endl;
    outputStream<<value2<<endl;
    QString rue ="";
    QString ville ="";
    QString code_postal="";
    if(countad==2)
    {
        QStringList tokens = adresse.split(",");
       rue =tokens[0];
        ville =tokens[1];
        code_postal =tokens[2];
        if(tokens[0]==""||tokens[1]==""||tokens[2]=="")
            countad=-1;
    }
    int countref = 0;
    for (int i=0;i<ref.size();i++)
    {
        QChar c=ref[i];
        if (c == ","||c=="."||c=="*"||c=="/"||c=="-"||c=="&"||c=="#"||c=="'"||c=="("||c==")"||c=="["||c=="]"||c=="="||c=="+"||c=="%")
        {
            countref++;
        }
    }
    if(ref.size()==0)
        countref=5;

    if(countad<2||ref==""||countref>0)
    {
        test1=0;
    }
    if(test1==1&&ok1 && ok2)
    {
        Stations S(ref,statut,nbr_bornes,type_connect,rue,ville,code_postal,value1,value2);
        bool test=S.ajouter();
        if (test)
        {
            // Refresh
            ui->tableView->setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
        }
        ui->lineEdit_ref->setStyleSheet("background-color:white;border-radius:10px;");
        ui->lineEdit_adresse->setStyleSheet("background-color:white;border-radius:10px;");
        ui->lineEdit_adresse->update();
        ui->lineEdit_ref->update();
        ui->groupBox_ajout->hide();

    }
    else
    {
            if(countad<2)
            {
                ui->lineEdit_adresse->setStyleSheet("border: 2px solid red; background-color: white;border-radius:10px;");
                ui->lineEdit_adresse->update();
            }
            else
            {
                ui->lineEdit_adresse->setStyleSheet("background-color: white;border-radius:10px;");
                ui->lineEdit_adresse->update();
            }
            if(countref>0)
            {
                    ui->lineEdit_ref->setStyleSheet("border: 2px solid red; background-color: white;border-radius:10px;");
                    ui->lineEdit_ref->update();
            }
            else
            {
                ui->lineEdit_ref->setStyleSheet("background-color: white;border-radius:10px;");
                ui->lineEdit_ref->update();
            }
            if(ok1==false||ok2==false)
            {
                ui->lineEdit_adresse_2->setStyleSheet("border: 2px solid red; background-color: white;border-radius:10px;");
                ui->lineEdit_adresse_2->update();
            }
            else
            {
                ui->lineEdit_adresse_2->setStyleSheet("background-color: white;border-radius:10px;");
                ui->lineEdit_adresse_2->update();
            }
    }
}
void MainWindow::on_pushButton_annuler_ajout_clicked()
{
    ui->groupBox_ajout->hide();
}
void MainWindow::exportationpdf(const QString &fileName)
{
    QPdfWriter pdfWriter(fileName);
    QPainter painter(&pdfWriter);

    QColor color_green(0, 128, 0);
    QColor color_red(200, 0, 0);
    QColor color_blue(0, 0, 128);
    QColor color_purple(128, 0, 128);


    // Set up the painter
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    //New Page
    painter.begin(&pdfWriter);
    // Start a new page
    QFont font;
    int fontSize = 10;  // Adjust the font size as needed
    font.setPointSize(fontSize);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.begin(&pdfWriter);

    // Ajouter une section d'en-tête
    painter.drawText(0, 900, "Rapport Instantané sur l'Activité des Stations");

    painter.drawText(0,2300 , "Signature : Nom Prenom");
    painter.drawText(0, 2700, "Date de Création : " + QDate::currentDate().toString("dd/MM/yyyy"));
    painter.setPen(Qt::black);
    painter.drawText(3500, 1500, "Entreprise : GreenGO");
    painter.drawText(3400,3300 , "LISTE DES STATION");
    painter.drawLine(0, 1100, pdfWriter.width(),1100);


    int rowCount = tab.afficher(editableColumns,customDelegate->editrow,ch)->rowCount();
    int a=0;
    int b=0;
    int c=0;
    int d=0;
    painter.drawText(0, 4000, "Station n°" );
    painter.drawText(1000, 4000, "Reference" );
    painter.drawText(2000, 4000, "Statut" );
    painter.drawText(3200, 4000, "Nbr Connecteur" );
    painter.drawText(4700, 4000, "Type Connecteur" );
    painter.drawText(6600, 4000, "Adresse" );

    for (int row = 1; row < rowCount; ++row)
    {
        QModelIndex index1 = tab.afficher(editableColumns,customDelegate->editrow,ch)->index(row, 1);
        QVariant data1 = tab.afficher(editableColumns,customDelegate->editrow,ch)->data(index1);
        if(data1.toString()=="Ouverte")
            {painter.setPen(color_green);b++;}
        else
        {
            if(data1.toString()=="Occupe")
                {painter.setPen(color_red);a++;}
            else
            {
                if(data1.toString()=="Hors service")
                {painter.setPen(color_purple);c++;}
                else
                    {painter.setPen(color_blue);d++;}
            }
        }
        painter.drawText(2000, 4000+((row)*500), data1.toString());

        painter.drawText(250, 4000+((row)*500), QString::number(row));

        QModelIndex index = tab.afficher(editableColumns,customDelegate->editrow,ch)->index(row, 0);
        QVariant data = tab.afficher(editableColumns,customDelegate->editrow,ch)->data(index);
        painter.drawText(1000, 4000+((row)*500), data.toString());

        QModelIndex index2 = tab.afficher(editableColumns,customDelegate->editrow,ch)->index(row, 2);
        QVariant data2 = tab.afficher(editableColumns,customDelegate->editrow,ch)->data(index2);
        painter.drawText(3600, 4000+((row)*500), data2.toString());

        QModelIndex index3 = tab.afficher(editableColumns,customDelegate->editrow,ch)->index(row, 3);
        QVariant data3 = tab.afficher(editableColumns,customDelegate->editrow,ch)->data(index3);
        painter.drawText(4600, 4000+((row)*500), data3.toString());

        QModelIndex index4 = tab.afficher(editableColumns,customDelegate->editrow,ch)->index(row, 4);
        QVariant data4 = tab.afficher(editableColumns,customDelegate->editrow,ch)->data(index4);
        painter.drawText(6600, 4000+((row)*500), data4.toString());

    }
    // Afficher les informations sur les taxis dans le PDF
    painter.setPen(color_red);
    painter.drawText(0,5000+((rowCount)*500)+2500, "Nombre de Stations Occupés : " );
    painter.drawText(3500, 5000+((rowCount)*500)+2500, QString::number(a));

    painter.setPen(color_green);
    painter.drawText(0, 5000+((rowCount)*500)+3000, "Nombre de stations Ouverte : " );
    painter.drawText(3500, 5000+((rowCount)*500)+3000, QString::number(b));

    painter.setPen(color_purple);
    painter.drawText(0, 5000+((rowCount)*500)+3500, "Nombre de stations Hors Service : " );
    painter.drawText(3500, 5000+((rowCount)*500)+3500, QString::number(c));

    painter.setPen(color_blue);
    painter.drawText(0, 5000+((rowCount)*500)+4000, "Nombre de stations En Construction : " );
    painter.drawText(3500, 5000+((rowCount)*500)+4000, QString::number(d));

    painter.end();

}
/*
void MainWindow::on_pushButton_annule_supp_clicked()
{
    ui->groupBox_supp->hide();
}

void MainWindow::on_pushButton_valide_supp_clicked()
{
    QString ref =ui->lineEdit_ref_supp->text();
    bool test = tab.supprimer(ref);
    if (test)
    {
        // Refresh
        ui->tableView->setModel(tab.afficher());
    }
    ui->groupBox_supp->hide();
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    ui->groupBox_supp->show();
}
void MainWindow::on_pushButton_modifier_clicked()
{
    ui->groupBox_modif1->show();
}
QSqlQueryModel *MainWindow::recherchemodif()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM Stations WHERE ref = "+ui->lineEdit_ref_modif1->text()+"");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref"));
    return model;
}
QString MainWindow::on_pushButton_valide_modif1_clicked()
{
    QString ref1 =ui->lineEdit_ref_modif1->text();
    int countref=0;
    for (int i=0;i<ref1.size();i++)
    {
        QChar c=ref1[i];
        if (c == ","||c=="."||c=="*"||c=="/"||c=="-"||c=="&"||c=="#"||c=="'"||c=="("||c==")"||c=="["||c=="]"||c=="="||c=="+"||c=="%")
        {
            countref++;
        }
    }
    if(ref1.size()==0||recherchemodif()->rowCount()==0)
        countref=5;
    if(countref>0)
    {
        ui->groupBox_erreur->show();
        ui->label_erreur->setText("Refill Reference case");
    }

    else
    {
        ui->groupBox_erreur->hide();
        ui->groupBox_modif1->hide();
        ui->groupBox_modif2->show();
/*
        QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM Stations WHERE ref = "+ui->lineEdit_recherche->text()+"");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref"));
*//*
        QSqlQuery query;
        query.prepare("SELECT * FROM Stations WHERE ref = :ref");
      //  ui->comboBox_statut_modif->setCurrentText(query.value(":statut").toString());
        query.bindValue(":ref",ui->lineEdit_ref_modif1->text());

        int index = ui->comboBox_statut_modif->findText(query.value(0).toString());
        if (index != -1)
        {
            ui->comboBox_statut_modif->setCurrentIndex(index);
        }

        QTextStream out(stdout);
        out << index;
        out<<query.value(1).toString();

        out <<query.value(1).toString();

    }
    return ref1;
}
void MainWindow::on_pushButton_annule_modif1_clicked()
{
    ui->groupBox_erreur->hide();
    ui->groupBox_modif1->hide();
}
void MainWindow::on_pushButton_valide_modif2_clicked()
{

    QString ref1=on_pushButton_valide_modif1_clicked();
    QString statut = ui->comboBox_statut_modif->currentText();
    int nbr_bornes = ui->spinBox_nbr_bornes_modif->text().toInt();
    QString type_connect = ui->comboBox_type_connect_modif->currentText();
    QString adresse = ui->lineEdit_adresse_modif->text();
    QStringList tokens = adresse.split(",");
    QString rue =tokens[0];
    QString ville =tokens[1];
    QString code_postal =tokens[2];

    Stations S(ref1,statut,nbr_bornes,type_connect,rue,ville,code_postal);
    bool test=S.update();
    if (test)
    {
        // Refresh
        ui->tableView->setModel(tab.afficher());
    }
    ui->groupBox_modif2->hide();
}
void MainWindow::on_pushButton_annuler_modif2_clicked()
{
    ui->groupBox_modif2->hide();
}
*/
QSqlQueryModel *MainWindow::recherche()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT ref ,statut,nbr_bornes,type_connect, (rue || ', ' || ville || ',' || code_postal) AS adresse FROM Stations WHERE ref = "+ui->lineEdit_recherche->text()+"");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ref"));
    return model;
}
void MainWindow::on_pushButton_recherche_clicked()
{
    if((ui->tableView_2->isVisible())|| recherche()->rowCount()==0)
    {

        ui->tableView_2->hide();
        if(recherche()->rowCount()==0&&ui->lineEdit_recherche->text()!="")
        {

                ui->groupBox_recherche_introuvable->show();

        }
        else
            ui->groupBox_recherche_introuvable->hide();
    }
    else
    {
        ui->tableView_2->show();
        ui->tableView_2->setModel(recherche());
        ui->groupBox_recherche_introuvable->hide();
    }
}
void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked)
    ch="SELECT ref ,statut,nbr_bornes,type_connect, (rue || ', ' || ville || ',' || code_postal) AS adresse FROM Stations ORDER BY ref ASC";
    else
    ch="SELECT ref ,statut,nbr_bornes,type_connect, (rue || ', ' || ville || ',' || code_postal) AS adresse FROM Stations";
    ui->tableView->setModel(tab.afficher(editableColumns,customDelegate->editrow,ch));
}

void MainWindow::on_pushButton_exportation_clicked()
{
    QString pdfFilename="output.pdf";
    exportationpdf(pdfFilename);
}

///////////////////////////////////////mail
void MainWindow::sendmail()
{
    smtp* smtp = new class smtp (ui->uname->text(), ui->paswd->text(), "smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtp->sendMaile(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

}
void MainWindow::on_sendBtn_clicked()
{
    sendmail();
}
/*
void MainWindow::on_commandLinkButton_clicked()
{
    ui->groupBox_gestion_station_1->show();
    ui->label_statistic->hide();
    ui->commandLinkButton->hide();

    ui->commandLinkButton_02->show();
}

void MainWindow::on_commandLinkButton_02_clicked()
{
    ui->groupBox_gestion_station_1->hide();
    ui->label_statistic->show();
    ui->commandLinkButton->show();
    ui->commandLinkButton_02->hide();
}*/


