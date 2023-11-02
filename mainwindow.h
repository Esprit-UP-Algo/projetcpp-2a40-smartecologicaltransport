#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include <QMainWindow>
#include <taxi.h>
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
    void on_pushButton_3_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::MainWindow *ui;
    taxi T1,T2;
};
#endif // MAINWINDOW_H
