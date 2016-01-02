#ifndef KODIMYSQLDBTEST_H
#define KODIMYSQLDBTEST_H

// Qt
#include <QObject>
#include <QtTest>
#include <QSignalSpy>
#include <QCoreApplication>
#include <QDebug>

// system
#include <unistd.h>

// local
#include "../backends/kodimysqldatabase.h"
#include "../include/connection.h"
#include "../include/config.h"

const QString Host("192.168.1.5");
const int Port(3306);
const QString Username("xbmc");
const QString Password("xbmc");
const QString DatabaseName("MyVideos93");
const QString ConnectionName("KodiDb");
const QString Driver("QMYSQL3");
//const QString Driver("QMYSQL");

class KodiMysqlDbTest : public QObject
{
    Q_OBJECT
public slots:
    void finished();
    void results(const QString &query, const QList<QSqlRecord> &records, const QString &resultId);
private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup() {}

    // tests
    void testSetup();
    void testGetMovies();
    void testGetTvShows();
    void testSomething();
private:
    KodiMysqlDatabase *db;
    bool wait;
};
QTEST_GUILESS_MAIN(KodiMysqlDbTest)
#include "kodimysqldbtest.moc"
#endif

// *************************************
// *************************************
void KodiMysqlDbTest::finished()
{
    qDebug() << DEBUG_FUNCTION << "entered";
    wait = false;
}

void KodiMysqlDbTest::results(const QString &query, const QList<QSqlRecord> &records, const QString &resultId)
{
    qDebug() << "query: " << query;
    qDebug() << "resultId: " << resultId;
    Q_UNUSED(records);
}

void KodiMysqlDbTest::initTestCase()
{
    Connection connection;
    connection.host = Host;
    connection.port = Port;
    connection.username = Username;
    connection.password = Password;
    connection.databaseName = DatabaseName;
    connection.connectionName = ConnectionName;
    connection.driver = Driver;

    db = new KodiMysqlDatabase(&connection);

    db->start();
    //    connect(&db, SIGNAL())
    //QObject::connect(&db, SIGNAL(finished() ), this, SLOT(finished() ) );
}

void KodiMysqlDbTest::cleanupTestCase()
{
    db->end();
    //QTest::qWait(10000);
    delete db;
}

void KodiMysqlDbTest::init() { wait = true; }


void KodiMysqlDbTest::testSetup()
{
    //QSKIP("skip");
    QTest::qWait(1000);

    db->runQuery("genres", "select * from genre");
    QTest::qWait(3000);
    //db->runQuery("movies", "select * from movie_view");
    //QTest::qWait(10000);
    //while(wait)
    //    QCoreApplication::processEvents();
}

void KodiMysqlDbTest::testGetMovies()
{
    QSKIP("skip");
    /*
    db.selectMovieGenres();
    //db.selectMovies();

    //QSignalSpy spy(&db, SIGNAL(finished()) );

    while(wait)
        QCoreApplication::processEvents();
    //QTest::qWait(10000);
    //QCOMPARE(spy.count(), 1);

    wait = true;
    db.selectMovies();
    */
    while(wait)
        QCoreApplication::processEvents();
    //QTest::qWait(20000);
}

void KodiMysqlDbTest::testGetTvShows()
{
    QSKIP("skip");
}

void KodiMysqlDbTest::testSomething()
{
    db->doSomething();
}








