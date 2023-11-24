#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPropertyAnimation>
#include<QVector>
#include"bouttons.h"
#include"courses.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void animation_login();
    bool verifier(QString , QString);
    void state();
    void detecter_action();
    ~MainWindow();

private slots:
    void on_username_textChanged(const QString &arg1);

    void on_password_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_log_out_clicked();

    void on_home_clicked();

    void on_managment_clicked();

    void on_ges_course_clicked();

    void on_pushButton_3_clicked();

    void on_creer_clicked();

private:
    Ui::MainWindow *ui;
    /*annimation login*/
    QPropertyAnimation *an1;
    QPropertyAnimation *an2;
    int r1,r2;
    int pas;
    boutton *btn;
    /*annimation login*/
    tab_course t_cour;
    Course_line *l;
    bouttons sup[10];
    bouttons modifier[10];
    QString role;

};

#endif // MAINWINDOW_H
