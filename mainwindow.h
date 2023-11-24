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
#include <QList>
#include "mycustomdelegate.h"
#include "editablesqlquerymodel.h"
#include <QGraphicsOpacityEffect>
#include <QTextDocumentWriter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QTextCursor>
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include <QApplication>
#include <QCommandLinkButton>
#include <QTransform>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
    bool edit=false;
        QList<int> editableColumns;
        Ui::MainWindow *ui;
        Stations tab;
        QTableView liste1,liste2;

        MyCustomDelegate* customDelegate=new MyCustomDelegate;
        bool updateColumnsFlag = true;
    public:
QString ch="SELECT ref ,statut,nbr_bornes,type_connect, (rue || ', ' || ville || ',' || code_postal) AS adresse FROM Stations";
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void TableWidgetDisplay();
        void exportationpdf(const QString &fileName);
        void applyshadow();
        QSqlQueryModel *recherche();
        QSqlQueryModel *recherchemodif();

       // void on_editButton_clicked(const QModelIndex& index);
        void on_pushButton_management_clicked();
    private slots:

            void on_pushButton_valide_ajout_clicked();
            void on_pushButton_annuler_ajout_clicked();
        /*    void on_pushButton_valide_supp_clicked();

            void on_pushButton_supprimer_clicked();
            void on_pushButton_annule_supp_clicked();
            void on_pushButton_modifier_clicked();
            QString on_pushButton_valide_modif1_clicked();
            void on_pushButton_valide_modif2_clicked();

            void on_pushButton_annule_modif1_clicked();
            void on_pushButton_annuler_modif2_clicked();*/
void on_pushButton_recherche_clicked();
        void edit_mode();
        void handle_update();
        void handle_delete();
        void on_pushButton_ajout_clicked();
        void on_radioButton_toggled(bool checked);
        void on_pushButton_exportation_clicked();
        void on_commandLinkButton_clicked();
        void on_commandLinkButton_02_clicked();
};

#endif // MAINWINDOW_H
