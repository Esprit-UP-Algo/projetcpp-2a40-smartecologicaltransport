#ifndef LINE_H
#define LINE_H
#include<QVector>
#include"mainwindow.h"
#include"boutton.h"
#include"lineedite.h"
class Line_tab
{
public:
    QRect pos;
    QVector<QLabel*> line;
    edite reference;
    QDateEdit  *date;
    QTimeEdit *time_D;
    QTimeEdit *time_F;
    edite tarif;
    edite adresse_D;
    edite adresse_F;
    edite meth_pay;
    QLabel *boutton[2];
    bouttons edit;
    bouttons sup;
    bouttons ajout;
    int test[5];
    Line_tab();
    Line_tab(QLabel*,QRect);
    Line_tab(QRect);
    void remplir(Line_tab);
    void initialiser();
    void style();
    ~Line_tab();
    void couvert();
    void afficher();
    void donner_acces();
    void blocker_acces();
    void deplacer(QRect);
    void vider();
    void controle_saisie();
    void annimer();
    bool verifier();
};
#endif // LINE_H
