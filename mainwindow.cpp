#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QDebug"
#include<QSqlQuery>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btn=new boutton(this);
    animation_login();
    ui->grp_interface->hide();
    ui->grp_login->show();
    Connection c;
    c.createconnect();
    t_cour=tab_course(ui->label_23,{100,250,1500,500});
    l=new Course_line({0,0,150,50},t_cour.lab_crud);
    l->couvert();
    detecter_action();
}
void MainWindow :: animation_login()
{
    an1 = new QPropertyAnimation(ui->label_5, "geometry");
    an2 = new QPropertyAnimation(ui->label_8, "geometry");
    an1->setDuration(500);
    an1->setStartValue(ui->label_5->geometry());
    an1->setEndValue(QRect(ui->label_5->pos().x(),ui->label_5->pos().y()-50,ui->label_5->width(),ui->label_5->height()));
    an2->setDuration(500);
    an2->setStartValue(ui->label_8->geometry());
    an2->setEndValue(QRect(ui->label_8->pos().x(),ui->label_8->pos().y()-50,ui->label_8->width(),ui->label_8->height()));
    r1=0;
    r2=0;
    ui->username->setTextMargins(57,0,0,0);
    ui->password->setTextMargins(57,0,0,0);
    ui->password->setEchoMode(QLineEdit::Password);
    QObject :: connect(btn,&QPushButton::clicked,[&]()
    {
        if(verifier(ui->username->text(),ui->password->text()))
        {
            ui->grp_login->hide();
            btn->hide();
            ui->grp_interface->show();
            ui->grp_ges_course->show();
            ui->grp_ges->hide();
        }
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_username_textChanged(const QString &)
{
    if(r1==0)
    {
        an1->start();
        r1=1;
    }
}

void MainWindow::on_password_textChanged(const QString &)
{
    if(r2==0)
    {
        an2->start();
        r2=1;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->password->echoMode() == QLineEdit ::Password )
    {
        ui->password->setEchoMode(QLineEdit :: Normal);
    }
    else
    {
        ui->password->setEchoMode(QLineEdit ::Password);
    }
}

void MainWindow::on_log_out_clicked()
{
    ui->grp_login->show();
    btn->show();
    ui->grp_interface->hide();
}

void MainWindow::on_home_clicked()
{
    ui->home->setStyleSheet("QPushButton {background:url(':/new/prefix1/image/interface/home_S.png');background-color:transparent;}");
    ui->managment->setStyleSheet("QPushButton {background:url(':/new/prefix1/image/interface/managment_NS.png');background-color:transparent;}"
                                                  "QPushButton:hover{border:1px solid;border-radius:20px}");
}

void MainWindow::on_managment_clicked()
{
    ui->home->setStyleSheet("QPushButton {background:url(':/new/prefix1/image/interface/home_NS.png');background-color:transparent;}"
                                                  "QPushButton:hover{border:1px solid;border-radius:20px}");
    ui->managment->setStyleSheet("QPushButton {background:url(':/new/prefix1/image/interface/managment_S.png');background-color:transparent;}");
}

void MainWindow::on_ges_course_clicked()
{
    if(role=="course")
    {
        ui->grp_ges->show();
        ui->grp_ges_course->hide();
    }
}

void MainWindow::on_pushButton_3_clicked()
{

    ui->grp_ges->hide();
    ui->grp_ges_course->hide();
}
bool MainWindow:: verifier(QString username,QString pas)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM perso WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next())
    {
        role =query.value(4).toString();
        qDebug() << role;
        return query.value(3).toString()==pas;
    }
    return false;
}

void MainWindow::on_creer_clicked()
{
    l->deplacer({0,(1+t_cour.nbr_l)*50,150,50});
    l->afficher();
}
void MainWindow :: detecter_action()
{
    for(int i=0;i<10;i++)
    {
        sup[i]=bouttons(t_cour.lab_crud,{1250,50+50*i,50,50},"background-color:transparent;","","");
        modifier[i]=bouttons(t_cour.lab_crud,{1200,50+50*i,50,50},"background-color:transparent;","","");
        QObject::connect(sup[i].b,&QPushButton::clicked,[&]()
        {
            QPoint globalPos = QCursor::pos();
            int mouseY = globalPos.y();
            int indice=((mouseY-400)/50)-1;
            qDebug() << "indice: " << indice;
            if(indice>=0 && indice<t_cour.nbr_l)
            {
                t_cour.suprimer_tab(indice);
            }

        });
        QObject::connect(modifier[i].b, &QPushButton::clicked, [&]()
        {
            QPoint globalPos = QCursor::pos();
            int mouseY = globalPos.y();
            int indice=((mouseY-400)/50)-1;

            if (indice >= 0 && indice < t_cour.tab.size())
            {
                t_cour.tab[indice]->couvert();
                qDebug() << "indice= " << indice;
                Course_line *l=new Course_line(t_cour.tab[indice]->pos,t_cour.lab_crud);
                l->remplir(t_cour.tab[indice]);
                l->afficher();
            }
        });
    }
}
