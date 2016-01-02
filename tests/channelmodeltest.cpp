#ifndef CHANNELMODELTEST_H
#define CHANNELMODELTEST_H

// Qt
#include <QtTest>
#include <QDebug>
// local
#include "../src/models/channelmodel.h"

class ChannelModelTest : public QObject
{
    Q_OBJECT
private:
    void initVideoItems();
    void initChannels();
    VideoItem *videoItem1;
    VideoItem *videoItem2;
    Channel *channel1;
    Channel *channel2;
    ChannelModel model;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void init() {}
    void cleanup() {}
    // tests
    void testVideoItem();
    void testChannel();
    void testChannelModel();
};
QTEST_GUILESS_MAIN(ChannelModelTest)
#include "channelmodeltest.moc"
#endif

void ChannelModelTest::initVideoItems()
{
    videoItem1 = new VideoItem();
    videoItem2 = new VideoItem();
    videoItem1->setTitle("SampleTitle1");
    videoItem1->setSummary("sample summary 1");
    videoItem1->setFile("/path/to/movie1.mkv");
    videoItem1->setStartTime(QTime(1, 00, 00) );
    videoItem1->setEndTime(QTime(2, 30, 5) );
    videoItem1->setLength(QTime(1, 30, 05) );
    videoItem2->setTitle("SampleTitle2");
    videoItem2->setSummary("sample summary 2");
    videoItem2->setFile("/path/to/movie2.mkv");
    videoItem2->setStartTime(QTime(1, 30, 06) );
    videoItem2->setEndTime(QTime(2, 56, 10) );
    videoItem2->setLength(QTime(1, 26, 04) );
}

void ChannelModelTest::initChannels()
{
    channel1 = new Channel();
    channel2 = new Channel();
    channel1->setType(Channel::Type::TvShow);
    channel1->setNumber(1);
    channel1->setDescription("channel 1");
    channel2->setType(Channel::Type::Movie);
    channel2->setNumber(2);
    channel2->setDescription("channel 2");
}

void ChannelModelTest::initTestCase()
{
    initVideoItems();
    initChannels();
}

void ChannelModelTest::cleanupTestCase()
{
    model.clear();
    QCOMPARE(model.rowCount(), 0);
    QCOMPARE(model.isEmpty(), true);
}

void ChannelModelTest::testVideoItem()
{
    QCOMPARE(videoItem1->title(), QString("SampleTitle1") );
    QCOMPARE(videoItem1->summary(), QString("sample summary 1") );
    QCOMPARE(videoItem1->file(), QString("/path/to/movie1.mkv") );

    QCOMPARE(videoItem1->startTime().hour(), 1);
    QCOMPARE(videoItem1->startTime().minute(), 00);
    QCOMPARE(videoItem1->startTime().second(), 00);

    QCOMPARE(videoItem1->endTime().hour(), 2);
    QCOMPARE(videoItem1->endTime().minute(), 30);
    QCOMPARE(videoItem1->endTime().second(), 5);

    QCOMPARE(videoItem1->length().hour(), 1);
    QCOMPARE(videoItem1->length().minute(), 30);
    QCOMPARE(videoItem1->length().second(), 5);

    // next video itme
    QCOMPARE(videoItem2->title(), QString("SampleTitle2") );
    QCOMPARE(videoItem2->summary(), QString("sample summary 2") );
    QCOMPARE(videoItem2->file(), QString("/path/to/movie2.mkv") );

    QCOMPARE(videoItem2->startTime().hour(), 1);
    QCOMPARE(videoItem2->startTime().minute(), 30);
    QCOMPARE(videoItem2->startTime().second(), 06);

    QCOMPARE(videoItem2->endTime().hour(), 2);
    QCOMPARE(videoItem2->endTime().minute(), 56);
    QCOMPARE(videoItem2->endTime().second(), 10);

    QCOMPARE(videoItem2->length().hour(), 1);
    QCOMPARE(videoItem2->length().minute(), 26);
    QCOMPARE(videoItem2->length().second(), 4);
}

void ChannelModelTest::testChannel()
{
    QCOMPARE(channel1->isReady(), false);
    QCOMPARE(channel2->isReady(), false);
    channel1->setIsReady(true);
    channel2->setIsReady(true);
    QCOMPARE(channel1->isReady(), true);
    QCOMPARE(channel2->isReady(), true);


    QCOMPARE(channel1->type(), Channel::Type::TvShow);
    QCOMPARE(channel1->number(), 1);
    QCOMPARE(channel1->description(), QString("channel 1"));

    //QCOMPARE(channel1->conditionCount(), 0);
    //channel1->appendCondition(condition1);
    //QCOMPARE(channel1->conditionCount(), 1);
    //QCOMPARE(channel1->conditionAt(0)->column(), QString("genre") );
    // test out of bonds
    //QCOMPARE(channel1->conditionAt(1)->column(), QString("") );



    QCOMPARE(channel2->type(), Channel::Type::Movie);
    QCOMPARE(channel2->number(), 2);
    QCOMPARE(channel2->description(), QString("channel 2"));

    Channel *channelptr = new Channel(Channel::Type::Movie, 5);
    QCOMPARE(channelptr->type(), Channel::Type::Movie);
    QCOMPARE(channelptr->number(), 5);
    QCOMPARE(channelptr->isReady(), false);
    delete channelptr;


    // test video items in channels
    channel1->appendVideo(videoItem1);
    QCOMPARE(channel1->videoCount(), 1);
    QCOMPARE(channel1->videoAt(0)->title(), QString("SampleTitle1"));

    channel1->appendVideo(videoItem2);
    QCOMPARE(channel1->videoCount(), 2);
    QCOMPARE(channel1->videoAt(1)->title(), QString("SampleTitle2"));


    channel1->removeVideoAt(0);
    QCOMPARE(channel1->videoCount(), 1);
    QCOMPARE(channel1->videoAt(0)->title(), QString("SampleTitle2"));


    // remove last video, should return a pointer with title = invalid
    channel1->removeVideoAt(0);
    QCOMPARE(channel1->videoCount(), 0);
    QCOMPARE(channel1->videoAt(0)->title(), QString("invalid"));

    // pointers are deleted, re init them
    initVideoItems();

    channel1->appendVideo(videoItem1);
    channel1->appendVideo(videoItem2);
    QCOMPARE(channel1->videoCount(), 2);
    QCOMPARE(channel1->videoAt(2)->title(), QString("invalid"));

    channel1->clearVideos();
    QCOMPARE(channel1->videoCount(), 0);
    QCOMPARE(channel1->videoAt(1)->title(), QString("invalid"));
    QCOMPARE(channel1->videoAt(0)->title(), QString("invalid"));
    QCOMPARE(channel1->videoAt(-1)->title(), QString("invalid"));
    QCOMPARE(channel1->videoAt(200)->title(), QString("invalid"));

    initVideoItems();
    channel1->appendVideo(videoItem1);
    channel1->appendVideo(videoItem2);
    QCOMPARE(channel1->videoCount(), 2);
}

void ChannelModelTest::testChannelModel()
{
    // test appending
    QCOMPARE(model.isEmpty(), true);
    QCOMPARE(model.rowCount(), 0);
    model.append(channel1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.at(0)->number(), 1);
    model.append(channel2);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.at(1)->number(), 2);
    QCOMPARE(model.isEmpty(), false);

    // test removing
    model.removeAt(1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.at(0)->number(), 1);

    model.removeAt(0);
    QCOMPARE(model.rowCount(), 0);
    QCOMPARE(model.isEmpty(), true);
    // should return a newly recreate, invalid channel
    QCOMPARE(model.at(0)->number(), -1);
    QCOMPARE(model.at(0)->type(), Channel::Type::Null);

    initVideoItems();
    initChannels();

    QCOMPARE(channel1->isReady(), false);
    QCOMPARE(channel2->isReady(), false);

    // test inserting
    model.insert(0, channel1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.isEmpty(), false);
    QCOMPARE(model.at(0)->number(), 1);

    model.insert(1, channel2);
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.at(1)->number(), 2);

    // test finding channels
    Channel *tmp;
    tmp = model.findChannelByNumber(1);
    QCOMPARE(tmp->number(), 1);
    tmp = model.findChannelByNumber(2);
    QCOMPARE(tmp->number(), 2);
}











