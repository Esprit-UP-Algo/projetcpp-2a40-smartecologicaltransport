#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet");
    db.setUserName("nour");
    db.setPassword("Nawara20");

    if (db.open()) test=true;
    return  test;
}
void Connection :: closeConnection(){db.close();}
