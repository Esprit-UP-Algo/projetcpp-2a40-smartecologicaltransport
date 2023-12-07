#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduino.h"
#include <QTableView>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update_label();

    void on_editer_clicked();

    void on_return_2_clicked();

     void on_pushButton_16_clicked();

    void on_done_clicked();

    void on_pushButton_17_clicked();

    void on_modifier_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_20_clicked();

    void on_refrechini_clicked();

    void on_filtrini_clicked();

    void on_pdf_clicked();

    void on_return_3_clicked();

    void on_return_4_clicked();

    void on_pushButton_11_clicked();

    void on_ajouterp_clicked();

    void on_confp_clicked();

    void on_show_clicked();

    void on_pushButton_8_clicked();
    int count1();
    int count0();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_19_clicked();

    void on_pushButton_10_clicked();
void changer_etat_travaille(QString REFERENCE,QString etat);
bool etat_travaille();
private:
    Ui::MainWindow *ui;
    void exportToPNG(QTableView* tableView);
    QByteArray data; // variable contenant les données reçues
    QString ref;
    Arduino A;
};
#endif // MAINWINDOW_H
