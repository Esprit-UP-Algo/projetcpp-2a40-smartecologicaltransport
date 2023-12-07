#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include <QMainWindow>
#include <taxi.h>
#include<QFile>
#include<QDir>
#include<QDebug>
#include<QTextStream>
#include <QApplication>
#include <QPainter>
#include <QTextDocument>
#include<QGraphicsDropShadowEffect>
#include<QPropertyAnimation>
#include<QRect>
#include <QIntValidator>
#include <QFile>
#include <QTextStream>
#include<Windows.h>
#include"arduino.h"
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
    void update_ard();
    void on_pushButton_3_clicked();


    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_19_clicked();



    void on_pushButton_23_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();


    void on_pushButton_17_clicked();


    void on_pushButton_29_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();


    void on_pushButton_9_clicked();

    void on_pushButton_6_clicked();

    void notif();

    void on_pushButton_38_clicked();

    void on_NOTIF_clicked();

    void on_tableView_3_activated(const QModelIndex &index);

    void on_lineEdit_5_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    taxi T1,T2;
        QPropertyAnimation *ESS;
        QByteArray data;
    Arduino A;
};
#endif // MAINWINDOW_H
