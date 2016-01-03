#ifndef CHANNELMODELFROMJSONTEST_H
#define CHANNELMODELFROMJSONTEST_H

#include <QtTest>
#include "../src/json/channelmodelfromjson.h"
#include "../src/json/channelmodeltojson.h"
#include "../src/models/channelmodel.h"

const QString BasicJsonExample("../data/basicexample.json");
const QString WriteBasicJson("../data/basicwrite.json");

class ChannelModelFromJsonTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase() {}
    void init() {}
    void cleanup() {}
    // tests
    void testBasicJsonParsing();
    void testBasicJsonWriting();
private:
    ChannelModelFromJson *fromJson;
    ChannelModelToJson *toJson;
    ChannelModel model;

};
QTEST_GUILESS_MAIN(ChannelModelFromJsonTest)
#include "channelmodeljsontest.moc"
#endif

void ChannelModelFromJsonTest::initTestCase()
{
    QFile writeFile(WriteBasicJson);
    if(writeFile.exists() )
        writeFile.remove();
}

// tests
void ChannelModelFromJsonTest::testBasicJsonParsing()
{
    fromJson = new ChannelModelFromJson(BasicJsonExample);
    QCOMPARE(fromJson->parse(model), true);
    delete fromJson;

    // test channel 1
    Channel *channel = model.at(0);
    QCOMPARE(channel->number(), 1);
    QCOMPARE(channel->type(), Channel::Type::Movie);
    QCOMPARE(channel->description(), QString("channel 1") );
    // db criteria

    //QCOMPARE(channel->criteria().column(), QStringList() << "title" << "summary" <<
    //                                    "description");
    //QCOMPARE(channel->criteria().from(), QString("movies"));
    //QCOMPARE(channel->criteria().where().column(), QString("genre"));
    //QCOMPARE(channel->criteria().where().operation(), QString("like"));
    //QCOMPARE(channel->criteria().where().value(), QString("sci fi"));

    QCOMPARE(channel->criteria().hasWhere(), true);
    QCOMPARE(channel->criteria().whereCount(), 5);

    QCOMPARE(channel->criteria().where().at(0).column(), QString("genre"));
    QCOMPARE(channel->criteria().where().at(0).operation(), QString("like"));
    QCOMPARE(channel->criteria().where().at(0).value(), QString("action"));

    QCOMPARE(channel->criteria().where().at(1).column(), QString("genre"));
    QCOMPARE(channel->criteria().where().at(1).operation(), QString("like"));
    QCOMPARE(channel->criteria().where().at(1).value(), QString("drama"));

    QCOMPARE(channel->criteria().where().at(2).column(), QString("genre"));
    QCOMPARE(channel->criteria().where().at(2).operation(), QString("like"));
    QCOMPARE(channel->criteria().where().at(2).value(), QString("sci fi"));

    QCOMPARE(channel->criteria().where().at(3).column(), QString("genre"));
    QCOMPARE(channel->criteria().where().at(3).operation(), QString("like"));
    QCOMPARE(channel->criteria().where().at(3).value(), QString("fantasy"));

    QCOMPARE(channel->criteria().where().at(4).column(), QString("watchstatus"));
    QCOMPARE(channel->criteria().where().at(4).operation(), QString("is"));
    QCOMPARE(channel->criteria().where().at(4).value(), QString("true"));


    //QCOMPARE(channel->criteria().andList().at(0).column(), QString("genre"));
    //QCOMPARE(channel->criteria().andList().at(0).operation(), QString("like"));
    //QCOMPARE(channel->criteria().andList().at(0).value(), QString("drama"));
    //QCOMPARE(channel->criteria().andList().at(1).column(), QString("watchstatus"));
    //QCOMPARE(channel->criteria().andList().at(1).operation(), QString("is"));
    //QCOMPARE(channel->criteria().andList().at(1).value(), QString("true"));
    //QCOMPARE(channel->criteria().orderBy().column(), QString("title"));
    //QCOMPARE(channel->criteria().orderBy().value(), QString("DESC"));
    QCOMPARE(channel->criteria().limit(), 10);

    QCOMPARE(channel->videoAt(0)->title(), QString("video 1"));
    QCOMPARE(channel->videoAt(0)->summary(), QString("summary of video 1"));
    QCOMPARE(channel->videoAt(0)->file(), QString("/path/to/movie1.mkv"));
    QCOMPARE(channel->videoAt(0)->startTime(), QTime(1, 00));
    QCOMPARE(channel->videoAt(0)->endTime(), QTime(2, 32));
    QCOMPARE(channel->videoAt(0)->length(), QTime(1, 32));

    QCOMPARE(channel->videoAt(1)->title(), QString("video 2"));
    QCOMPARE(channel->videoAt(1)->summary(), QString("summary of video 2"));
    QCOMPARE(channel->videoAt(1)->file(), QString("/path/to/movie2.mkv"));
    QCOMPARE(channel->videoAt(1)->startTime(), QTime(2, 33));
    QCOMPARE(channel->videoAt(1)->endTime(), QTime(3, 33));
    QCOMPARE(channel->videoAt(1)->length(), QTime(1, 00));

    QCOMPARE(channel->videoAt(2)->title(), QString("invalid"));

    // test channel 2
    channel = model.at(1);
    QCOMPARE(channel->number(), 2);
    QCOMPARE(channel->type(), Channel::Type::TvShow);
    QCOMPARE(channel->description(), QString("channel 2") );
    // db criteria
    QCOMPARE(channel->criteria().isEmpty(), true);

    QCOMPARE(channel->videoAt(0)->title(), QString("video 1"));
    QCOMPARE(channel->videoAt(0)->summary(), QString("summary of video 1"));
    QCOMPARE(channel->videoAt(0)->file(), QString("/path/to/movie1.mkv"));
    QCOMPARE(channel->videoAt(0)->startTime(), QTime(1, 00));
    QCOMPARE(channel->videoAt(0)->endTime(), QTime(2, 32));
    QCOMPARE(channel->videoAt(0)->length(), QTime(1, 32));

    QCOMPARE(channel->videoAt(1)->title(), QString("video 2"));
    QCOMPARE(channel->videoAt(1)->summary(), QString("summary of video 2"));
    QCOMPARE(channel->videoAt(1)->file(), QString("/path/to/movie2.mkv"));
    QCOMPARE(channel->videoAt(1)->startTime(), QTime(2, 33));
    QCOMPARE(channel->videoAt(1)->endTime(), QTime(3, 33));
    QCOMPARE(channel->videoAt(1)->length(), QTime(1, 01));

    QCOMPARE(channel->videoAt(2)->title(), QString("video 3"));
    QCOMPARE(channel->videoAt(2)->summary(), QString("summary of video 3"));
    QCOMPARE(channel->videoAt(2)->file(), QString("/path/to/movie3.mkv"));
    QCOMPARE(channel->videoAt(2)->startTime(), QTime(3, 34));
    QCOMPARE(channel->videoAt(2)->endTime(), QTime(4, 34));
    QCOMPARE(channel->videoAt(2)->length(), QTime(1, 00));

    QCOMPARE(channel->videoAt(3)->title(), QString("invalid"));
}

void ChannelModelFromJsonTest::testBasicJsonWriting()
{
    //QSKIP("skip");
    toJson = new ChannelModelToJson(WriteBasicJson);
    toJson->write(model);
    delete toJson;

    QString file1, file2;
    QFile orgFile, newFile;
    orgFile.setFileName(BasicJsonExample);
    newFile.setFileName(WriteBasicJson);

    QCOMPARE(orgFile.open(QIODevice::ReadOnly | QIODevice::Text), true);
    QCOMPARE(newFile.open(QIODevice::ReadOnly | QIODevice::Text), true);

    file1 = orgFile.readAll();
    file2 = newFile.readAll();
    orgFile.close();
    newFile.close();

    QCOMPARE(file1.size(), 2698);
    QCOMPARE(file2.size(), 2698);
    QCOMPARE(file1, file2);

    file2.append("extra data");
    QVERIFY(file1 != file2);
}










