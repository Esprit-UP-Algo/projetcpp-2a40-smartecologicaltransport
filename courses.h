#ifndef COURSES_H
#define COURSES_H

#include"lineedite.h"
#include"bouttons.h"
#include"connection.h"
#include<QFrame>
#include<QPixmap>
#include <iostream>
#include<QPropertyAnimation>
#include<QPushButton>
#include<QCheckBox>
#include<QTimer>
#include<QDateEdit>
#include<QTimeEdit>
#include<QComboBox>

class Date
{
public:
    int jours;
    int mois;
    int annes;
};
class Time
{
public:
    int heure;
    int minute;
};

class Courses
{
public:
    int REFERENCE;
    Date DATE;
    Time HEURE_D;
    Time HEURE_F;
    int TARIF;
    QString ADRESSE_D;
    QString ADRESSE_F;
    Courses();
};
class Case
{
public:
    QFont font;
    QLabel *lab;
    QLabel *line;
    Case();
    Case(QRect pos,QLabel *l);
    void line_red();
    void line_green();
    void line_gray();
};

class Course_line
{
public:
    int test[5];
    Courses info; //pour stoque les information de chaque course
    QRect pos; // pour stoquer la position de la ligne
    QVector<Case> line;
    edite reference;
    QDateEdit  *date;
    QTimeEdit *time_D;
    QTimeEdit *time_F;
    edite tarif;
    edite adresse_D;
    edite adresse_F;
    QComboBox *meth_pay;
    QLabel *boutton[4];
    QCheckBox select;
    bouttons_img *modifer;
    bouttons_img *sup;
    bouttons_img *valide;

public:
    Course_line();
    Course_line(QRect,QLabel*);
    Course_line(QRect,QLabel*,Courses);
    void initialiser();
    void style();
    void remplir(Course_line*);
    void couvert();
    void afficher();
    void donner_acces();
    void blocker_acces();
    void deplacer(QRect);
    void vider();
    void controle_saisie();
    void annimer();
    bool verifier();
    void ligne_color(QString);
};
class Crud_Course
{
public:
    Crud_Course();
    QSqlQuery req_select();
    QSqlQuery req_ajout(Course_line);
    QSqlQuery query;
};
class tab_course
{
public:
    int nbr_ajout;
    int nbr_sup;
    int nbr_mod;
    int nbr_l;
    QRect pos;
    QLabel *lab_crud;
    QVector<Case>titre;
    QVector<Course_line*> tab;
    //Crud_Course crud;
public:
    tab_course();
    tab_course(QLabel*,QRect pos);
    void initialiser_tab();
    void remplir_tab();
    int recherche_tab(QString);
    void ajouter_tab(Course_line );
    void suprimer_tab(int);
    void trie_tab();
    void afficher_tab();
    void couvert_tab();
    void intialiser_titre();
    void detecter_action();
};

#endif // COURSES_H
