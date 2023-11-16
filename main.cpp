#include "mainwindow.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;//une seule instance
    bool test=c.createconnect();//etablir la connexion
    MainWindow w;
    w.show();
    //ALLERTE
    QPropertyAnimation *ESS1;
    return a.exec();
}
