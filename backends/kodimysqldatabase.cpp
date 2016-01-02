// Qt
#include <QDebug>

#include "kodimysqldatabase.h"
#include "querythread.h"
#include "../include/connection.h"
#include "../include/config.h"

KodiMysqlDatabase::KodiMysqlDatabase(Connection *connection)
    : mQuerythread(nullptr), mConnection(connection) {}

KodiMysqlDatabase::~KodiMysqlDatabase()
{
    if(mQuerythread)
        delete mQuerythread;
}

void KodiMysqlDatabase::start()
{
    qDebug() << DEBUG_FUNCTION << "entered";
    mQuerythread = new QueryThread();
    if(mConnection != 0) {
        mQuerythread->setHost(mConnection->host);
        mQuerythread->setUsername(mConnection->username);
        mQuerythread->setPassword(mConnection->password);
        mQuerythread->setDatabaseName(mConnection->databaseName);
        mQuerythread->setConnectionName(mConnection->connectionName);
        mQuerythread->setDriver(mConnection->driver);
        mQuerythread->setPort(mConnection->port);
    }

    connect(mQuerythread, SIGNAL(progress(QString)),this, SLOT(process(QString)) );
    connect(mQuerythread, SIGNAL(ready(bool) ), this, SLOT(ready(bool) ) );
    connect(mQuerythread, SIGNAL(results(QString,QList<QSqlRecord>,QString)), this, SLOT(slotResults(QString,QList<QSqlRecord>,QString)) );

    mQuerythread->start();
}

void KodiMysqlDatabase::end()
{
    mQuerythread->exit(0);
    mQuerythread->wait();
}

void KodiMysqlDatabase::runQuery(const QString &queryId, const QString &query)
{
    mQuerythread->execute(queryId, query);
}

void KodiMysqlDatabase::doSomething() const
{
    qDebug() << DEBUG_FUNCTION << "KodiMysqlDatabase::doSomething() Called";
}

void KodiMysqlDatabase::slotResults(const QString &queryId, const QList<QSqlRecord> &records, const QString &resultId)
{
    qDebug() << DEBUG_FUNCTION_SHORT << "entered";

    qDebug() << "\n";
    qDebug() << "queryId: "  << queryId;
    qDebug() << "returned " << records.count() << " records";
    //qDebug() << "records: "  << records;
    qDebug() << "resultId: " << resultId;
}

void KodiMysqlDatabase::process(QString msg)
{
    qDebug() << DEBUG_FUNCTION << msg;
}

void KodiMysqlDatabase::ready(bool ready)
{
    qDebug() << DEBUG_FUNCTION << "ready: " << ready;
    if(ready) {
        //mQuerythread->execute("select movies", "select * from genre");
        //mQuerythread->execute("select movies", "select * from movie_view");
        //m_querythread->execute("select * from movies", "");
    }
}






























