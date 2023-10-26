#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
inter :: inter()
{

}


inter :: inter(QMainWindow *w)
{
    lab=new QLabel(w);
    sh=new QGraphicsDropShadowEffect;
    titre=new QLabel(lab);
}
inter :: inter(QLabel *l)
{
    lab=new QLabel(l);
    sh=new QGraphicsDropShadowEffect;
    titre=new QLabel(lab);
}
inter :: inter(QMainWindow *w,QRect pos,QString style,QString t)
{
    lab=new QLabel(w);
    sh=new QGraphicsDropShadowEffect;
    titre=new QLabel(lab);
    lab->setGeometry(pos);
    lab->setStyleSheet(style);
    sh->setColor(QColor("gris"));
    sh->setBlurRadius(50);
    sh->setOffset(0,0);
    lab->setGraphicsEffect(sh);
    if(t[0]!='\0')
    {
        img.load(t);
        titre->setPixmap(img);
        titre->resize(img.size());
        titre->move((pos.width()-titre->width())/2,20);
    }
    else
    {
        delete titre;
        titre=NULL;
    }
}
inter :: ~inter()
{

}
btn_crud :: btn_crud(QLabel *l,QRect pos,QString titre ,QString image)
{
    QFont font;
    press=0;
    b=new QPushButton(l);
    lab=new QLabel(b);
    img.load(image);
    font.setPointSize(20);
    b->setFont(font);
    b->setText(titre);
    lab->resize(img.size());
    lab->setPixmap(img);
    lab->setStyleSheet("background-color:transparent;");
    lab->move(10,10);
    b->setGeometry(pos);
    b->setStyleSheet("QPushButton {background-color: #ebebeb; border-radius: 20px; color: white;}"
                     "QPushButton:hover {background-color: #ebebeb; border-radius: 20px; border: 2px solid; color: white;}");


    QObject :: connect (b,&QPushButton :: clicked ,[&]()
    {
       if(press==0)
       {
           b->setStyleSheet("QPushButton {background-color:white ; border-radius: 20px; color: #ebebeb;}"
                            "QPushButton:hover {background-color:white; border-radius: 20px; border: 2px solid; color: #ebebeb;}");
           press=1;
       }
       else
       {
           b->setStyleSheet("QPushButton {background-color: #ebebeb; border-radius: 20px; color: white;}"
                            "QPushButton:hover {background-color: #ebebeb; border-radius: 20px; border: 2px solid; color: white;}");
           press=0;
       }
    });
}

btn_crud :: btn_crud()
{

}
