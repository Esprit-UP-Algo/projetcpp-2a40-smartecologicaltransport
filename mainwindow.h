#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include <QGraphicsView>
#include<QGraphicsDropShadowEffect>
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <QTableView>
#include <QGroupBox>
#include <QStringList>
#include "stations.h"
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow *ui;
        Stations tab;
        QTableView liste1,liste2;
        QGraphicsDropShadowEffect *shadow;
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void TableWidgetDisplay();
        void applyshadow();
QSqlQueryModel *recherche();


        void on_pushButton_management_clicked();
    private slots:
            void on_pushButton_ajout_clicked();
            void on_pushButton_valide_ajout_clicked();
            void on_pushButton_valide_supp_clicked();
            void on_pushButton_annuler_ajout_clicked();
            void on_pushButton_supprimer_clicked();
            void on_pushButton_annule_supp_clicked();
            void on_pushButton_modifier_clicked();
            QString on_pushButton_valide_modif1_clicked();
            void on_pushButton_valide_modif2_clicked();
            void on_pushButton_recherche_clicked();
};
class bckg
{
    QLabel *label;
    QGraphicsDropShadowEffect *shadow;
    public:
        bckg(MainWindow &w);
        void style(int x,int y,int w,int h,QString ch1,QString ch2);

        ~bckg();
};
class btn
{
    QPushButton *Button;
    public:
        btn(MainWindow &w);//img
        btn(MainWindow &w,QString ch);//txt
        ~btn();
        void style(int x,int y,int w,int h,QString ch);

};
#endif // MAINWINDOW_H
