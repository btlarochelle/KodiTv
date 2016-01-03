#ifndef KODIMYSQLDBTEST_H
#define KODIMYSQLDBTEST_H

// Qt
#include <QObject>
#include <QtTest>
#include <QSignalSpy>
#include <QCoreApplication>
#include <QTime>
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
private:
    void wait();
    KodiMysqlDatabase *db;
    bool mWait;
public slots:
    void finished();
    void results(const QString &query, const QList<QSqlRecord> &records,
                 const QString &resultId);
private slots:
    void initTestCase();
    void cleanupTestCase();
    void init() { mWait = true; }
    void cleanup() {}

    // tests
    void testQueries();
    void testGetMovieGenres();
    void testGetMovies();
    void testGetTvShows();
    void testSomething();

};
QTEST_GUILESS_MAIN(KodiMysqlDbTest)
#include "kodimysqldbtest.moc"
#endif

// *************************************
// *************************************

// private
void KodiMysqlDbTest::wait()
{
    QTime time = QTime::currentTime();
    while(mWait) {
        QCoreApplication::processEvents();
        if(time.elapsed() > 3000) {
            qDebug() << "breaking timeout";
            break;
        }
    }
    mWait = true;
}

// public slots
void KodiMysqlDbTest::finished()
{
    mWait = false;
}

void KodiMysqlDbTest::results(const QString &query, const QList<QSqlRecord> &records, const QString &resultId)
{
    qDebug() << "query: " << query;
    qDebug() << "resultId: " << resultId;
    qDebug() << "records: " << records;

    Q_UNUSED(records);
}

// private slots
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
    QObject::connect(db, SIGNAL(finished() ), this, SLOT(finished() ) );
}

void KodiMysqlDbTest::cleanupTestCase()
{
    db->end();
    //QTest::qWait(10000);
    delete db;
}

// tests
void KodiMysqlDbTest::testQueries()
{
    //QSKIP("skip");
    QTest::qWait(1000); // wait for worker it get ready
    QString tmp;

    tmp.append("select distinct(name) from genre ");
    tmp.append("join genre_link on genre.genre_id=genre_link.genre_id ");
    tmp.append("and genre_link.media_type='movie' ");
    tmp.append("order by name asc");

    db->runQuery("movie_genres", tmp);
    wait();

    tmp.clear();
    tmp.append("select distinct(name) from genre ");
    tmp.append("join genre_link on genre.genre_id=genre_link.genre_id ");
    tmp.append("and genre_link.media_type='tvshow' ");
    tmp.append("order by name asc");

    db->runQuery("tvshow_genres", tmp);
    wait();

    tmp.clear();
    tmp.append("select * from movie_view ");
    tmp.append("join genre_link on genre_link.media_id=movie_view.idMovie ");
    tmp.append("and genre_link.media_type='movie' ");
    tmp.append("join genre on genre.genre_id=genre_link.genre_id ");
    tmp.append("where genre.name like 'Horror' ");
    tmp.append("order by rand() ");
    tmp.append("limit 10 ");

    db->runQuery("movies", tmp);
    wait();
}

void KodiMysqlDbTest::testGetMovieGenres()
{
    QSKIP("skip");
    QTest::qWait(1000); // wait for worker it get ready
    QString tmp;

    /*
    tmp.append("select distinct(name) from genre ");
    tmp.append("join genre_link on genre.genre_id=genre_link.genre_id ");
    tmp.append("and genre_link.media_type='movie'");
    db->runQuery("movie_genres", tmp);
    QTest::qWait(3000);

    //while(wait)
    //    QCoreApplication::processEvents();

    tmp.clear();
    tmp.append("select distinct(name) from genre ");
    tmp.append("join genre_link on genre.genre_id=genre_link.genre_id ");
    tmp.append("and genre_link.media_type='tvshow'");
    db->runQuery("tvshow_genres", tmp);
    QTest::qWait(3000);
    */


    tmp.clear();
    tmp.append("select * from movie_view ");
    tmp.append("join genre_link on genre_link.media_id=movie_view.idMovie ");
    tmp.append("and genre_link.media_type='movie' ");
    tmp.append("join genre on genre.genre_id=genre_link.genre_id ");
    tmp.append("where genre.name like 'Horror' ");
    db->runQuery("movies", tmp);
    QTest::qWait(3000);
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








