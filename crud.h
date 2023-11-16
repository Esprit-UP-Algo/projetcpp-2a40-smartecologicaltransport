#ifndef CRUD_H
#define CRUD_H
#include"boutton.h"
#include"line.h"
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>

class Crud
{
public:
    int y;
    bouttons ajout;
    QRect pos;
    QLabel *lab_crud;
    QVector<QLabel*>titre;
    QVector<Line_tab> tab;
    QVector<Line_tab> tab_ajout;
    QVector<Line_tab> tab_sup;
    QVector<Line_tab>tab_modifier;
    int nbr_ajout;
    int nbr_sup;
    int nbr_mod;
    int nbr_l;
    void initialiser_tab();
    int recherche_tab(QString);
    void ajouter_tab(Line_tab );
    void suprimer_tab(int);
    void trie_tab();
    void afficher_tab();
    void deafficher_tab();
    Crud(QLabel*,QRect pos);
    Crud();
    ~Crud();
    void intialiser_titre();
    void annimer();
    void req_ajout();
    void req_sup();
    void req_select();
    void req_modifier();
    int s;
    int compter(QString);
    void stat(QLabel* lab);
    void pdf(MainWindow*);
    void modifier(Line_tab , int);
    void exel(MainWindow*);
};

#endif // CRUD_H
