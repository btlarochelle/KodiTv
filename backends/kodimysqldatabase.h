#ifndef KODIMYSQLDATABASE_H
#define KODIMYSQLDATABASE_H

#include <QObject>
#include <QtPlugin>
#include <QList>
#include <QString>
#include <QSqlRecord>

#include "../include/backendplugininterface.h"

class QSqlDatabase;
class QueryThread;
class Connection;

class KodiMysqlDatabase : public QObject, public BackendPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.KodiTv.BackendPluginInterface" )
    Q_INTERFACES(BackendPluginInterface)
public:
    KodiMysqlDatabase(Connection *connection = 0);
    ~KodiMysqlDatabase();

    void start();
    void end();
    void runQuery(const QString &queryId, const QString &query);

    // plugin interface
    void doSomething() const;
signals:
    void finished();
private slots:
    void slotResults(const QString &queryId, const QList<QSqlRecord> &records, const QString &resultId);
    void process(QString msg);
    void ready(bool ready);
private:
    QueryThread *mQuerythread;
    Connection *mConnection;
};

#endif




