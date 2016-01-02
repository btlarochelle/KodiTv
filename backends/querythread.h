/*  taken from :
    http://www.linuxjournal.com/article/9602?page=0,0
    Asynchronous Database Access with Qt 4.x
    Jun 01, 2007	 By Dave Berton
*/

#ifndef QUERYTHREAD_H
#define QUERYTHREAD_H

#include <QList>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QString>
#include <QHash>

class SqlWorker : public QObject
{
    Q_OBJECT
public:
    explicit SqlWorker( QObject* parent = 0);
    ~SqlWorker();
    bool connect(const QString &host, const QString &username, const QString &password,
                 const QString dbname, const QString &driver, const QString &connectionName = "");
public slots:
    void slotExecute(const QString &queryId, const QString &sql);
    void slotExecutePrepared(const QString &queryId, const QString &resultId = QString());
    void slotPrepare(const QString &queryId, const QString &sql);
    void slotBindValue(const QString &queryId, const QString &placeholder, const QVariant &val);
signals:
    void executed(const QString &queryId, const QString &resultId);
    void executeFailed(const QString &queryId, const QSqlError &err, const QString &resultId);
    void prepared(const QString &queryId);
    void prepareFailed(const QString &queryId, const QSqlError &err);
    void results(const QString &queryId, const QList<QSqlRecord> &records, const QString &resultId);
private:
    QSqlDatabase mDatabase;
    QHash<QString, QSqlQuery*> mQueries;
    void executeOneTime(const QString &queryId, const QString &sql);
    void executePrepared(const QString &queryId, const QString &resultId = QString());
};


class QueryThread : public QThread
{
    Q_OBJECT
public:
    explicit QueryThread(QObject *parent = 0);
    ~QueryThread();

    void setHost(const QString &host);
    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void setDatabaseName(const QString &databaseName);
    void setConnectionName(const QString &connectionName);
    void setDriver(const QString &driver);
    void setPort(const int &port);

    void execute(const QString &queryId, const QString &sql);
    void executePrepared(const QString &queryId, const QString &resultId = QString());
    void prepare(const QString &queryId, const QString &sql);
    void bindValue(const QString &queryId, const QString &placeholder, const QVariant &val);
signals:
    void progress( const QString &msg);
    void ready(bool);
    void executed(const QString &queryId, const QString &resultId);
    void executeFailed(const QString &queryId, const QSqlError &err, const QString &resultId);
    void prepared(const QString &queryId);
    void prepareFailed(const QString &queryId, const QSqlError &err);
    void results(const QString &queryId, const QList<QSqlRecord> &records, const QString &resultId);
protected:
    void run();
signals:
    void fwdExecute(const QString &queryId, const QString &sql);
    void fwdExecutePrepared(const QString &queryId, const QString &resultId = QString());
    void fwdPrepare(const QString &queryId, const QString &sql);
    void fwdBindValue(const QString &queryId, const QString &placeholder, const QVariant &val);
private:
    SqlWorker *mWorker;
    QString mHost;
    QString mUsername;
    QString mPassword;
    QString mDatabaseName;
    QString mConnectionName;
    QString mDriver;
    int mPort;
};

#endif
