// Qt
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

// local
#include "querythread.h"
#include "../include/config.h"

SqlWorker::SqlWorker(QObject* parent) : QObject(parent) {}

SqlWorker::~SqlWorker()
{
    qDeleteAll(mQueries);

    if(mDatabase.isOpen() ) {
        mDatabase.close();
        QString conn = mDatabase.connectionName();
        mDatabase = QSqlDatabase();
        QSqlDatabase::removeDatabase(conn);
    }
}

bool SqlWorker::connect(const QString &host, const QString &username, const QString &password,
                        const QString dbname, const QString &driver, const QString &connectionName)
{
    mDatabase = QSqlDatabase::addDatabase(driver, connectionName);
    mDatabase.setDatabaseName(dbname);
    mDatabase.setHostName(host);
    mDatabase.setUserName(username);
    mDatabase.setPassword(password);

    if(!mDatabase.open() ) {
        qDebug() << DEBUG_FUNCTION << mDatabase.lastError().text();
        qWarning() << "Unable to connect to database, giving up:" << mDatabase.lastError().text();
        return false;
    }
    return true;
}

// public slots
void SqlWorker::slotExecute(const QString& queryId, const QString& sql)
{
    // if sql is not valid, treat this as already prepared statment
    // that needs to be executed
    bool isPrepared = (sql.isEmpty() || sql.isNull());

    if (isPrepared)
        executePrepared(queryId);
    else
        executeOneTime(queryId, sql);
}

void SqlWorker::slotExecutePrepared(const QString &queryId, const QString &resultId)
{
    executePrepared(queryId, resultId);
}

void SqlWorker::slotPrepare(const QString &queryId, const QString &sql)
{
    if(mQueries.contains(queryId)) {
        qDebug() << QString("already prepared query id [%1]").arg(queryId);
        return;
    }
    QSqlQuery *query;
    query = new QSqlQuery(mDatabase);
    bool ok = query->prepare(sql);

    if(!ok) {
        qDebug() << DEBUG_FUNCTION << QString("prepare failed for query id [%1]").arg(queryId);
        emit prepareFailed(queryId, query->lastError());
        return;
    }

    mQueries.insert(queryId, query);
    emit prepared(queryId);
}

void SqlWorker::slotBindValue(const QString &queryId, const QString &placeholder, const QVariant &val)
{
    if(!mQueries.contains(queryId)) {
        qDebug() << DEBUG_FUNCTION << QString("prepared query id [%1] not found").arg(queryId);
        return;
    }

    // get query from hash
    QSqlQuery *query;
    query = mQueries.value(queryId);
    // bind value
    query->bindValue(placeholder, val);
}

// private
void SqlWorker::executeOneTime(const QString& queryId, const QString& sql)
{
    QSqlQuery query(mDatabase);
    bool ok = query.exec(sql);
    if(!ok) {
        qDebug() << DEBUG_FUNCTION << QString("execute failed for one time query id [%1]").arg(queryId);
        qDebug() << DEBUG_FUNCTION << query.lastError();
        emit executeFailed(queryId, query.lastError(), QString());
        return;
    }

    emit executed(queryId, QString());
    QList<QSqlRecord> recs;
    while(query.next()) {
        recs.append(query.record());
    }
    emit results(queryId, recs, QString());
}

void SqlWorker::executePrepared(const QString& queryId, const QString &resultId)
{
    // constuct result_id, if not set
    QString newResultId;
    if(resultId.isEmpty() || resultId.isNull())
        newResultId = QString("queryresult_%1").arg(QDateTime::currentMSecsSinceEpoch());
    else
        newResultId = resultId;

    // check if there is query with specified id
    if(!mQueries.contains(queryId)) {
        qDebug() << DEBUG_FUNCTION << QString("prepared query id [%1] not found").arg(queryId);
        return;
    }
    // get query from hash
    QSqlQuery *query;
    query = mQueries.value(queryId);
    // execute and check query status
    bool ok = query->exec();

    if(!ok) {
        qDebug() << DEBUG_FUNCTION << QString("execute failed for prepared query id [%1]").arg(queryId);
        emit executeFailed(queryId, query->lastError(), newResultId);
        return;
    }
    // send executed signal
    emit executed(queryId, newResultId);

    QList<QSqlRecord> recs;
    while(query->next()) {
        recs.append(query->record());
    }
    // result saved - release resources
    query->finish();
    // send results signal
    emit results(queryId, recs, newResultId);
}

// **************************************
// ********** QueryThread ***************

QueryThread::QueryThread(QObject *parent) : QThread(parent), mWorker(nullptr) {}

QueryThread::~QueryThread()
{
    delete mWorker;
}

// public
void QueryThread::setHost(const QString &host)
{
    mHost = host;
}

void QueryThread::setUsername(const QString &username)
{
    mUsername = username;
}

void QueryThread::setPassword(const QString &password)
{
    mPassword = password;
}

void QueryThread::setDatabaseName(const QString &databaseName)
{
    mDatabaseName = databaseName;
}

void QueryThread::setConnectionName(const QString &connectionName)
{
    mConnectionName = connectionName;
}

void QueryThread::setDriver(const QString &driver)
{
    mDriver = driver;
}

void QueryThread::setPort(const int &port)
{
    mPort = port;
}

void QueryThread::execute(const QString &queryId, const QString &sql)
{
    emit fwdExecute(queryId, sql);
}

void QueryThread::executePrepared(const QString &queryId, const QString &resultId)
{
    emit fwdExecutePrepared(queryId, resultId);
}

void QueryThread::prepare(const QString &queryId, const QString &sql)
{
    emit fwdPrepare(queryId, sql);
}

void QueryThread::bindValue(const QString &queryId, const QString &placeholder, const QVariant &val)
{
    emit fwdBindValue(queryId, placeholder, val);
}

// protected
void QueryThread::run()
{
    emit ready(false);
    emit progress(QString("Starting, one moment please...") );

    // Create worker object within the context of the new thread
    mWorker = new SqlWorker();
    if(!mWorker->connect(mHost, mUsername, mPassword, mDatabaseName, mDriver, mConnectionName) )
        return;

    connect(this, SIGNAL(fwdExecute(QString,QString)), mWorker, SLOT(slotExecute(QString,QString)) );
    connect(this, SIGNAL(fwdExecutePrepared(QString,QString)), mWorker, SLOT(slotExecutePrepared(QString,QString)) );
    connect(this, SIGNAL(fwdPrepare(QString,QString)), mWorker, SLOT(slotPrepare(QString,QString)) );
    connect(this, SIGNAL(fwdBindValue(QString,QString,QVariant)), mWorker, SLOT(slotBindValue(QString,QString,QVariant)) );

    // Critical: register new type so that this signal can be
    // dispatched across thread boundaries by Qt using the event
    // system
    qRegisterMetaType<QList<QSqlRecord> >("QList<QSqlRecord>");

    // forward final signals
    connect(mWorker, SIGNAL(results(QString,QList<QSqlRecord>,QString)), this, SIGNAL(results(QString,QList<QSqlRecord>,QString)) );
    connect(mWorker, SIGNAL(executed(QString,QString)), this, SIGNAL(executed(QString,QString)) );
    connect(mWorker, SIGNAL(executeFailed(QString,QSqlError,QString)), this, SIGNAL(executeFailed(QString,QSqlError,QString)) );
    connect(mWorker, SIGNAL(prepared(QString)), this, SIGNAL(prepared(QString)) );
    connect(mWorker, SIGNAL(prepareFailed(QString,QSqlError)), this, SIGNAL(prepareFailed(QString,QSqlError)) );

    emit progress("SqlWorker ready to accept query request." );
    emit ready(true);

    exec();
}




