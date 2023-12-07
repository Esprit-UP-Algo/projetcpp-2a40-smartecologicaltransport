#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlDatabase>
#include<QDebug>

class Connection
{
    QSqlDatabase db;
    public:
        Connection();
        bool createconnection();
        void closeConnection();
};
#endif // CONNECTION_H
