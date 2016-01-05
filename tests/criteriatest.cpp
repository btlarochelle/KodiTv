#ifndef CRITERIATEST_H
#define CRITERIATEST_H

#include <QtTest>
#include "../src/models/criteria.h"

class CriteriaTest : public QObject
{
    Q_OBJECT
private:
    Criteria criteria;
private slots:
    void initTestCase() {}
    void cleanupTestCase();
    void init() {}
    void cleanup() {}
    // tests
    void testColumns();
    void testFrom();
    void testWhere();
    void testAnd();
    void testLimit();
    void testOrderBy();
    void testResultingQuery();
};
QTEST_GUILESS_MAIN(CriteriaTest)
#include "criteriatest.moc"
#endif

void CriteriaTest::cleanupTestCase()
{
    criteria.clear();
    QCOMPARE(criteria.isEmpty(), true);
    //QCOMPARE(criteria.column().isEmpty(), true);
    //QCOMPARE(criteria.from(), QString(""));
    QCOMPARE(criteria.where().isEmpty(), true);
    //QCOMPARE(criteria.andList().isEmpty(), true);
    QCOMPARE(criteria.limit(), 0);
    //QCOMPARE(criteria.orderBy().isEmpty(), true);
}

void CriteriaTest::testColumns()
{
    //SKIP("skipping");
    /*
    QCOMPARE(criteria.isEmpty(), true);

    criteria.appendColumn("title");
    QCOMPARE(criteria.columnCount(), 1);
    QCOMPARE(criteria.isEmpty(), false);

    criteria.appendColumn("summary");
    QCOMPARE(criteria.columnCount(), 2);

    criteria.appendColumn("description");
    QCOMPARE(criteria.columnCount(), 3);

    criteria.appendColumn("runtime");
    QCOMPARE(criteria.columnCount(), 4);

    QCOMPARE(criteria.column(), QStringList() << "title" << "summary"
                                << "description" << "runtime");
    */
}

void CriteriaTest::testFrom()
{
    //QSKIP("skipping");
    //criteria.setFrom("movies");
    //QCOMPARE(criteria.from(), QString("movies") );
    //QCOMPARE(criteria.isEmpty(), false);
}

void CriteriaTest::testWhere()
{
    QCOMPARE(criteria.hasWhere(), false);
    criteria.addWhere("genre", "like", "sci fi");
    criteria.addWhere("genre", "like", "action");
    criteria.addWhere("genre", "like", "drama");
    criteria.addWhere("watchstatus", "is", "true");
    QCOMPARE(criteria.whereCount(), 4);
    QCOMPARE(criteria.hasWhere(), true);

    QCOMPARE(criteria.where().at(0).column(), QString("genre"));
    QCOMPARE(criteria.where().at(0).operation(), QString("like"));
    QCOMPARE(criteria.where().at(0).value(), QString("sci fi"));

    QCOMPARE(criteria.where().at(1).column(), QString("genre"));
    QCOMPARE(criteria.where().at(1).operation(), QString("like"));
    QCOMPARE(criteria.where().at(1).value(), QString("action"));

    QCOMPARE(criteria.where().at(2).column(), QString("genre"));
    QCOMPARE(criteria.where().at(2).operation(), QString("like"));
    QCOMPARE(criteria.where().at(2).value(), QString("drama"));

    QCOMPARE(criteria.where().at(3).column(), QString("watchstatus"));
    QCOMPARE(criteria.where().at(3).operation(), QString("is"));
    QCOMPARE(criteria.where().at(3).value(), QString("true"));
}

void CriteriaTest::testAnd()
{
    //QSKIP("skipping");
    /*
    QCOMPARE(criteria.andCount(), 0);
    criteria.addAnd("genre", "like", "action");
    criteria.addAnd("genre", "like", "drama");
    criteria.addAnd("watchstatus", "is", "true");
    QCOMPARE(criteria.andCount(), 3);

    QCOMPARE(criteria.andList().at(0).column(), QString("genre"));
    QCOMPARE(criteria.andList().at(0).operation(), QString("like"));
    QCOMPARE(criteria.andList().at(0).value(), QString("action"));

    QCOMPARE(criteria.andList().at(1).column(), QString("genre"));
    QCOMPARE(criteria.andList().at(1).operation(), QString("like"));
    QCOMPARE(criteria.andList().at(1).value(), QString("drama"));

    QCOMPARE(criteria.andList().at(2).column(), QString("watchstatus"));
    QCOMPARE(criteria.andList().at(2).operation(), QString("is"));
    QCOMPARE(criteria.andList().at(2).value(), QString("true"));
    */
}

void CriteriaTest::testLimit()
{
    criteria.setLimit(50);
    QCOMPARE(criteria.limit(), 50);
    criteria.setLimit(10);
    QCOMPARE(criteria.limit(), 10);
}

void CriteriaTest::testOrderBy()
{
    //QSKIP("skipping");
    //QCOMPARE(criteria.hasOrderBy(), false);
    //criteria.setOrderBy("title", "DESC");
    //QCOMPARE(criteria.hasOrderBy(), true);
    //QCOMPARE(criteria.orderBy().column(), QString("title"));
    //QCOMPARE(criteria.orderBy().value(), QString("DESC"));
}

void CriteriaTest::testResultingQuery()
{

    //QString q("select title, summary, description, runtime ");
    //q.append("from movies ");
    //q.append("where genre like sci fi ");
    //q.append("and genre like action and genre like drama ");
    //q.append("and watchstatus is true ");
    //q.append("order_by title DESC ");
    //q.append("limit 10");
    QString q;
    q.append("where genre like sci fi ");
    q.append("and genre like action ");
    q.append("and genre like drama ");
    q.append("and watchstatus is true ");
    q.append("limit 10");
    QCOMPARE(criteria.toString(), q);
}





