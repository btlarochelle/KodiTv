#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>

struct Connection {
    QString host;
    QString username;
    QString password;
    QString databaseName;
    QString connectionName;
    QString driver;
    int port;
};


#endif




