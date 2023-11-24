#include"courses.h"
#include<QDebug>
Crud_Course::Crud_Course()
{

}
QSqlQuery Crud_Course :: req_select()
{
    query.prepare("SELECT * FROM course");
    if (!query.exec())
    {
        qDebug() << "Échec de la requête : " << query.lastError().text();
    }
    return  query;
}
QSqlQuery Crud_Course ::req_ajout(Course_line l)
{
    query.prepare("INSERT INTO course (REFERENCES, DATE_C, HEURE_D, HEURE_F, TARIF, ADRESSE_D, ADRESS_F, METHODE_P) "
                          "VALUES (:ref, TO_DATE(:date, 'YYYY-MM-DD'), :heure_d, :heure_f, :tarif, :adresse_d, :adresse_f, :methode_p)");
    QString dateText = l.date->date().toString("yyyy-MM-dd");
    QString heureFText = l.time_F->time().toString("HH:mm:ss");
    if (heureFText.length() > 20)
    {
        heureFText = heureFText.left(20);
    }
    query.bindValue(":ref", l.reference.get_text());
    query.bindValue(":date", dateText);
    query.bindValue(":heure_d", l.time_D->time().toString("HH:mm:ss"));
    query.bindValue(":heure_f", heureFText);
    query.bindValue(":tarif", l.tarif.get_text());
    query.bindValue(":adresse_d", l.adresse_D.get_text());
    query.bindValue(":adresse_f", l.adresse_F.get_text());
    query.bindValue(":methode_p", l.meth_pay->currentText());
    return query;
}
Case:: Case()
{

}
Case:: Case(QRect pos,QLabel *l)
{
    font.setPointSize(14);
    lab=new QLabel(l);
    line=new QLabel(lab);
    lab->setGeometry(pos);
    line->setGeometry(0,lab->geometry().height()-3,lab->geometry().width(),3);
    line->setStyleSheet("background-color:gray;");
    lab->setFont(font);
}
void Case:: line_red()
{
    line->setStyleSheet("background-color:red;");
}
void Case:: line_green()
{
    line->setStyleSheet("background-color:green;");
}
void Case:: line_gray()
{
    line->setStyleSheet("background-color:gray;");
}
Courses:: Courses()
{
    REFERENCE=0;
    DATE.jours=0;
    DATE.mois=0;
    DATE.annes=0;
    HEURE_D.heure=0;
    HEURE_D.minute=0;
    HEURE_F.heure=0;
    HEURE_F.minute=0;
    TARIF=0;
    ADRESSE_F="";
    ADRESSE_D="";

}
Course_line:: Course_line()
{

}
Course_line:: Course_line(QRect p,QLabel *lab)
{
    pos=p;
    Case c;
    for(int i=0;i<9;i++)
    {
        c=Case({pos.x()+i*pos.width(),pos.y(),pos.width(),pos.height()},lab);
        line.push_back(c);
    }
    initialiser();
    style();
    controle_saisie();

}

void Course_line :: initialiser()
{
    for(int i=0;i<5;i++) test[i]=0;
    reference=edite(line[0].lab,{0,0,pos.width(),pos.height()});
    date=new QDateEdit (line[1].lab) ;
    time_D=new QTimeEdit(line[2].lab);
    time_F=new QTimeEdit(line[3].lab);
    tarif=edite(line[4].lab,{0,0,pos.width(),pos.height()});
    adresse_D=edite(line[5].lab,{0,0,pos.width(),pos.height()});
    adresse_F=edite(line[6].lab,{0,0,pos.width(),pos.height()});
    meth_pay=new QComboBox(line[7].lab);
    modifer=new bouttons_img(line[8].lab,{0,0,50,50},":/new/prefix1/image/tab_ges_course/modifier.png",":/new/prefix1/image/tab_ges_course/modifier.png");
    valide= new bouttons_img(line[8].lab,{0,0,50,50},":/new/prefix1/image/tab_ges_course/valide.png",":/new/prefix1/image/tab_ges_course/valide.png");
    sup=new bouttons_img(line[8].lab,{50,0,50,50},":/new/prefix1/image/tab_ges_course/nonvalide.png",":/new/prefix1/image/tab_ges_course/nonvalide.png");
    modifer->hide();
    sup->show();
}
void Course_line :: style()
{
    date->resize(line[1].lab->size());
    time_D->resize(line[2].lab->size());
    time_F->resize(line[3].lab->size());
    meth_pay->addItem("enligne");
    meth_pay->addItem("cache");

    meth_pay->resize(line[3].lab->size());
}
void Course_line:: blocker_acces()
{
    reference.blocker_acces();
    date->setReadOnly(true);
    time_D->setReadOnly(true);
    time_F->setReadOnly(true);
    tarif.blocker_acces();
    adresse_D.blocker_acces();
    adresse_F.blocker_acces();
    meth_pay->setEnabled(true);
}
void Course_line :: donner_acces()
{
    reference.donner_acces();
    date->setReadOnly(false);
    time_D->setReadOnly(false);
    time_F->setReadOnly(false);
    tarif.donner_acces();
    adresse_D.donner_acces();
    adresse_F.donner_acces();
    meth_pay->setEnabled(false);
}
void Course_line ::deplacer(QRect p)
{
    pos=p;
    for(int i=0;i<9;i++)
    {
        line[i].lab->setGeometry(pos.x()+i*pos.width(),pos.y(),pos.width(),pos.height());
    }
}
void Course_line :: vider()
{
    reference.vider();
    adresse_D.vider();
    adresse_F.vider();
    tarif.vider();
    meth_pay->clear();
}
void Course_line :: remplir(Course_line *l)
{
    reference.set_text(l->reference.ed->text());
    date->setDate(l->date->date());
    time_D->setTime(l->time_D->time());
    time_F->setTime(l->time_F->time());
    tarif.set_text(l->tarif.ed->text());
    adresse_D.set_text(l->adresse_D.ed->text());
    adresse_F.set_text(l->adresse_F.ed->text());
    meth_pay->setCurrentText(l->meth_pay->currentText());

    //blocker_acces();

}
void Course_line :: afficher()
{
    for(int i=0;i<9;i++)
    {
        line[i].lab->show();
    }

}
void Course_line :: couvert()
{
    for(int i=0;i<9;i++)
    {
        line[i].lab->hide();
    }
}
void Course_line :: controle_saisie()
{
    QDoubleValidator validator;
    reference.ed->setValidator(new QIntValidator(100,99999));
    tarif.ed->setValidator(new QIntValidator(100,99999));
    QObject :: connect(reference.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=reference.get_text();
        if(ch.length()>=4)
        {
            reference.lab->setStyleSheet("background-color:green");
            test[0]=1;
        }
        else
        {
            reference.lab->setStyleSheet("background-color:red");
            test[0]=0;
        }
    });

    QObject :: connect(tarif.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=tarif.get_text();
        if(ch.length()>=2)
        {
            tarif.lab->setStyleSheet("background-color:green");
            test[1]=1;
        }
        else
        {
            tarif.lab->setStyleSheet("background-color:red");
            test[1]=0;
        }
    });
    QObject :: connect(adresse_D.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=adresse_D.get_text();
        if(ch.length()>=2)
        {
            adresse_D.lab->setStyleSheet("background-color:green");
            test[2]=1;
        }
        else
        {
            adresse_D.lab->setStyleSheet("background-color:red");
            test[2]=0;
        }
    });
    QObject :: connect(adresse_F.ed ,&QLineEdit :: textChanged,[&]()
    {
        QString ch;
        ch=adresse_F.get_text();
        if(ch.length()>=2)
        {
            adresse_F.lab->setStyleSheet("background-color:green");
            test[3]=1;
        }
        else
        {
            adresse_F.lab->setStyleSheet("background-color:red");
            test[3]=0;
        }
    });
}
bool Course_line :: verifier()
{
    int i=0;
    while(i<4 && test[i]!=0)
    {
        i++;
    }
    return i==5;
}
void Course_line:: ligne_color(QString color)
{
    if(color=="red")
    {
        for(int i=0;i<9;i++)
        {
            line[i].line_red();
        }
    }
    else if(color=="green")
    {
        for(int i=0;i<9;i++)
        {
            line[i].line_green();
        }
    }
    else
    {
        for(int i=0;i<9;i++)
        {
            line[i].line_gray();
        }
    }
}
//
tab_course:: tab_course()
{

}
tab_course:: tab_course(QLabel*l,QRect pos)
{
    nbr_l=0;
    nbr_ajout=0;
    nbr_mod=0;
    nbr_sup=0;
    lab_crud=new QLabel(l);
    lab_crud->setGeometry(pos);
    //lab_crud->setStyleSheet("border:2px solid;border-radius:20px;");
    intialiser_titre();
    remplir_tab();
    afficher_tab();

}
void tab_course:: intialiser_titre()
{
    Case c;
    for(int i=0;i<9;i++)
    {
        c=Case({150*i,0,150,50},lab_crud);
        titre.push_back(c);
    }
    titre[0].lab->setText("Reference");
    titre[1].lab->setText(" Date");
    titre[2].lab->setText("Time_D");
    titre[3].lab->setText("Time_F");
    titre[4].lab->setText("Tarif");
    titre[5].lab->setText("Adresse_D");
    titre[6].lab->setText("Adresse_F");
    titre[7].lab->setText("Methode_p");
}
void tab_course :: remplir_tab()
{
    Crud_Course crud;
    QSqlQuery query=crud.req_select();
    if(query.exec())
    {
        while (query.next())
        {
            Course_line *l=new Course_line({0,(1+nbr_l)*50,150,50},lab_crud);
            l->reference.set_text(query.value(0).toString());
            l->date->setDate(QDate::fromString(query.value(1).toString(), "yyyy-MM-dd"));
            l->time_D->setTime(QTime::fromString(query.value(2).toString(), "hh:mm:ss"));
            l->time_F->setTime(QTime::fromString(query.value(3).toString(), "hh:mm:ss"));
            l->tarif.set_text(query.value(4).toString());
            l->adresse_D.set_text(query.value(5).toString());
            l->adresse_F.set_text(query.value(6).toString());
            l->meth_pay->setCurrentText(query.value(7).toString());
            l->blocker_acces();
            l->ligne_color("gray");
            l->valide->hide();
            l->modifer->show();
            l->sup->show();
            tab.push_back(l);
            nbr_l++;
        }
    }
}
void tab_course :: detecter_action()
{
    QObject::connect(tab[nbr_l-1]->sup, &QPushButton::clicked, [&]()
    {
        QPoint globalPos = QCursor::pos();
        int mouseY = globalPos.y();
        int indice=((mouseY-400)/50)-1;
        if(indice>=0 && indice<tab.size())
        {
            nbr_sup++;
            suprimer_tab(indice);
        }
    });
    QObject::connect(tab[nbr_l-1]->modifer, &QPushButton::clicked, [&]()
    {
        QPoint globalPos = QCursor::pos();
        int mouseY = globalPos.y();
        int indice=((mouseY-400)/50)-1;

        if (indice >= 0 && indice < tab.size())
        {
            tab[indice]->couvert();
            Course_line *l=new Course_line(tab[indice]->pos,lab_crud);
            l->remplir(tab[indice]);
            QObject :: connect(l->valide,&QPushButton::clicked,[&]()
            {
                tab[indice]=l;
            });
            tab[indice]->afficher();
        }

    });
}


void tab_course :: suprimer_tab(int indice)
{
    couvert_tab();
    for(int i=indice;i<nbr_l-1;i++)
    {
        tab[i]=tab[i+1];
        tab[i]->deplacer({0,50*(i+1),150,50});
    }
    nbr_l--;

    afficher_tab();
}


void tab_course :: trie_tab()
{
   Course_line *l= new Course_line;
   QRect pos;
   int test;
   do
   {
       test=1;
       for(int i=0;i<nbr_l-1;i++)
       {
           qDebug () << tab[i]->tarif.get_text().toInt();
           if(tab[i]->tarif.get_text().toInt()>tab[i+1]->tarif.get_text().toInt())
           {
               test=0;
               l=tab[i];
               tab[i]=tab[i+1];
               tab[i+1]=l;


               pos=tab[i]->pos;
               tab[i]->deplacer(tab[i+1]->pos);
               tab[i+1]->deplacer(pos);

           }
       }
   }
   while(test==0);
}
void tab_course :: afficher_tab()
{

    for(int i=0;i<nbr_l;i++)
    {
        tab[i]->afficher();
    }
}
void tab_course :: couvert_tab()
{
    for(int i=0;i<nbr_l;i++)
    {
        tab[i]->couvert();
    }
}
