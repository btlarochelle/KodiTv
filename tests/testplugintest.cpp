#ifndef TESTPLUGINTEST_H
#define TESTPLUGINTEST_H

#include <QTest>

class TestPluginTest : public QObject {
    Q_OBJECT
private slots:
    void t1() { QVERIFY(true); }
};

QTEST_MAIN(TestPluginTest)
#include "testplugintest.moc"



#endif

