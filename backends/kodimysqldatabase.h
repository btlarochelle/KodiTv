#ifndef KODIMYSQLDATABASE_H
#define KODIMYSQLDATABASE_H

#include <QObject>
#include <QtPlugin>
#include <QList>
#include <QString>
#include <QSqlRecord>

#include "../include/backendplugininterface.h"
#include "../include/connection.h"

class ChannelModel;
class QSqlDatabase;
class QueryThread;

class KodiMysqlDatabase : public QObject, public BackendPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.KodiTv.BackendPluginInterface" )
    Q_INTERFACES(BackendPluginInterface)
public:
    KodiMysqlDatabase();
    KodiMysqlDatabase(Connection connection);

    ~KodiMysqlDatabase();

    void start();
    void end();
    void runQuery(const QString &queryId, const QString &query);

    void getMovieGenres();
    void getTvShowGenres();
    void getMoviesByGenre(const QString &queryId, const QString &genre);

    // plugin interface
    void loadModel(ChannelModel *model);
signals:
    void finished();
private slots:
    void slotResults(const QString &queryId, const QList<QSqlRecord> &records, const QString &resultId);
    void process(QString msg);
    void ready(bool ready);
private:
    QueryThread *mQuerythread;
    ChannelModel *model;
    Connection mConnection;
    int currentIndex;
};

#endif




