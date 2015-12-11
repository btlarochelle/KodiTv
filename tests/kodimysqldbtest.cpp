#ifndef KODIMYSQLDBTEST_H
#define KODIMYSQLDBTEST_H

#include <QObject>
#include <QtTest>
#include <QDebug>

#include "../backends/kodimysqldatabase.h"

class KodiMysqlDbTest : public QObject
{
    Q_OBJECT
public slots:
private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testSomething();

private:
    //KodiMysqlDatabase *db;
    KodiMysqlDatabase db;

};
QTEST_MAIN(KodiMysqlDbTest)
#include "kodimysqldbtest.moc"
#endif

// *************************************
// *************************************
void KodiMysqlDbTest::initTestCase()
{
    qDebug() << "inittestcase";
    //db = new KodiMysqlDatabase();
}

void KodiMysqlDbTest::cleanupTestCase()
{
    qDebug() << "cleanup test case";
    //delete db;
}

void KodiMysqlDbTest::init() {}
void KodiMysqlDbTest::cleanup() {}

void KodiMysqlDbTest::testSomething()
{
    db.doSomething();
}




