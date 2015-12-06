#ifndef KODIMYSQLDBTEST_H
#define KODIMYSQLDBTEST_H

#include <QtTest>

class KodiMysqlDbTest : public QObject
{
    Q_OBJECT
public slots:


private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

};
QTEST_MAIN(KodiMysqlDbTest)
#include "kodimysqldbtest.moc"
#endif




#include <QDebug>

void KodiMysqlDbTest::initTestCase()
{
    qDebug() << "inittestcase";
}

void KodiMysqlDbTest::cleanupTestCase()
{
    qDebug() << "cleanup test case";
}

void KodiMysqlDbTest::init()
{
    qDebug() << "Init";
}

void KodiMysqlDbTest::cleanup()
{
    qDebug() << "cleanup";
}
