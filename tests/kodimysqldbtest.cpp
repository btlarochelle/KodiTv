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
#include "../src/models/channelmodel.h"
#include "../src/json/channelmodeltojson.h"
#include "../include/config.h"


const QString Host("192.168.1.5");
const int Port(3306);
const QString Username("xbmc");
const QString Password("xbmc");
const QString DatabaseName("MyVideos93");
const QString ConnectionName("KodiDb");
const QString Driver("QMYSQL3");
//const QString Driver("QMYSQL");

const QString ChannelData("../data/channelData.json");

class KodiMysqlDbTest : public QObject
{
    Q_OBJECT
private:
    void wait();
    KodiMysqlDatabase *db;
    bool mWait;
    ChannelModel model;
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
    void testLoadModel();
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

    db = new KodiMysqlDatabase(connection);

    //db->start();
    QObject::connect(db, SIGNAL(finished() ), this, SLOT(finished() ) );
}

void KodiMysqlDbTest::cleanupTestCase()
{
    db->end();
    //QTest::qWait(1000);
    delete db;
}

// tests
void KodiMysqlDbTest::testQueries()
{
    QSKIP("skip");
    db->start();
    QTest::qWait(1000); // wait for worker it get ready
    db->getMovieGenres();
    wait();
    db->getTvShowGenres();
    wait();
    //db->getMoviesByGenre();
    //wait();
}

void KodiMysqlDbTest::testLoadModel()
{

}

void KodiMysqlDbTest::testSomething()
{
    Channel *channel = new Channel();
    channel->setNumber(1);
    channel->setType(Channel::Type::Movie);
    channel->setDescription("Action movies");
    channel->criteria().addWhere("genre", "like", "Action");
    model.append(channel);

    channel = new Channel();
    channel->setNumber(2);
    channel->setType(Channel::Type::Movie);
    channel->setDescription("Sci-Fi movies");
    channel->criteria().addWhere("genre", "like", "Sci-Fi");
    model.append(channel);

    channel = new Channel();
    channel->setNumber(3);
    channel->setType(Channel::Type::Movie);
    channel->setDescription("Animation movies");
    channel->criteria().addWhere("genre", "like", "Animation");
    model.append(channel);

    channel = new Channel();
    channel->setNumber(4);
    channel->setType(Channel::Type::Movie);
    channel->setDescription("Adventure movies");
    channel->criteria().addWhere("genre", "like", "Adventure");
    model.append(channel);

    channel = new Channel();
    channel->setNumber(5);
    channel->setType(Channel::Type::Movie);
    channel->setDescription("Comedy movies");
    channel->criteria().addWhere("genre", "like", "Comedy");
    model.append(channel);

    channel = new Channel();
    channel->setNumber(6);
    channel->setType(Channel::Type::Movie);
    channel->setDescription("Fantasy movies");
    channel->criteria().addWhere("genre", "like", "Fantasy");
    model.append(channel);


    QTest::qWait(1000); // wait for worker it get ready
    db->loadModel(&model);
    wait();

    ChannelModelToJson toJson(ChannelData);
    toJson.write(model);

}








