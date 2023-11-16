#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("TEST");
db.setUserName("sassi");//inserer nom de l'utilisateur
db.setPassword("12345678");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
return  test;
}
void Connection :: closeConnection()
{db.close();}
