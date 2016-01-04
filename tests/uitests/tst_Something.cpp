#ifndef TST_SOMETHING_H
#define TST_SOMETHING_H

#include <QtTest>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QUrl>

class tst_Something : public QObject
{
    Q_OBJECT
private:
    QQuickView *view;
private slots:
    void initTestCase();
    void cleanupTestCase() {}
    void init();
    void cleanup() {}
    // tests
    void test();
};
QTEST_MAIN(tst_Something)
#include "tst_Something.moc"
#endif


void tst_Something::initTestCase()
{
    view = new QQuickView(QGuiApplication::focusWindow());
    view->setSource(QString(QString(TEST_DIR) + QString("/tst_Something.qml")) );
    view->show();
}

void tst_Something::init()
{

}


void tst_Something::test()
{
    QTest::qWait(20000);
}
