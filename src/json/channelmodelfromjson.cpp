// Qt
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QTime>

// local
#include "channelmodelfromjson.h"
#include "../models/channelmodel.h"
#include "../models/criteria.h"
#include "../../include/config.h"

ChannelModelFromJson::ChannelModelFromJson(const QString &file)
{
    QString val;
    QFile jsonFile;
    jsonFile.setFileName(file);

    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << DEBUG_FUNCTION << "failed to open: " << file;
        return;
    }

    val = jsonFile.readAll();
    jsonFile.close();
    QJsonParseError parseError;
    document = QJsonDocument::fromJson(val.toUtf8(), &parseError);
    qDebug() << DEBUG_FUNCTION << "error: " << parseError.errorString();

}

// public
bool ChannelModelFromJson::parse(ChannelModel &model)
{
    if(document.isEmpty() || document.isNull()) {
        qDebug() << DEBUG_FUNCTION << "invalid json document";
        return false;
    }

    QJsonObject channels = document.object();

    if(channels.isEmpty() )
        return false;

    QJsonArray channelArray = channels["channels"].toArray();
    if(channelArray.isEmpty() )
        return false;

    foreach (const QJsonValue & value, channelArray) {
        Channel *channel = new Channel();
        QJsonObject channelObject = value.toObject();
        QJsonObject::iterator it;

        for(it = channelObject.begin(); it != channelObject.end(); it++) {
            if(it.key() == "criteria" ) {
                QJsonObject criteriaObject = it.value().toObject();
                parseCriteria(channel, criteriaObject);
                // channel.append(criteria);
            }
            else if(it.key() == "videos") {
                QJsonArray videoArray = channelObject["videos"].toArray();
                parseVideos(channel, videoArray);
            }
            else {
                parseChannel(channel, channelObject);
            }
        }
        model.append(channel);
    }
    return true;
}

// private
void ChannelModelFromJson::parseCriteria(Channel *channel, QJsonObject &object)
{
    QJsonObject::const_iterator it;
    for(it = object.begin(); it != object.end(); it++) {

        if(it.key() == "where" ) {
            foreach(const QJsonValue &value, it.value().toArray()) {

                QJsonObject::const_iterator columnsIter;
                QJsonObject columns = value.toObject();
                for(columnsIter = columns.begin(); columnsIter != columns.end(); columnsIter++) {

                    QJsonObject obj = columnsIter.value().toObject();
                    QJsonObject::const_iterator iter;
                    for(iter = obj.begin(); iter != obj.end(); iter++) {
                        channel->criteria().addWhere(columnsIter.key(), iter.key(), iter.value().toString());
                    }
                }

            }
        }
        else if(it.key() == "limit") {
            //qDebug() << "limit: " << it.value().toInt();
            channel->criteria().setLimit(it.value().toInt() );
        }
        else {
            //qDebug() << "key: " << it.key();
            //qDebug() << "value: " << it.value();
        }
    }
}

void ChannelModelFromJson::parseVideos(Channel *channel, QJsonArray &array)
{
    //qDebug() << DEBUG_FUNCTION << "entered";
    foreach(const QJsonValue &value, array) {
        VideoItem *video = new VideoItem();
        QJsonObject obj = value.toObject();
        foreach(const QJsonValue &value, obj) {
            Q_UNUSED(value);
            video->setTitle(obj["title"].toString() ) ;
            video->setSummary(obj["summary"].toString() );
            video->setFile(obj["file"].toString() );


            video->setStartTime(QTime::fromString(obj["startTime"].toString(),"h:mm" ));
            video->setEndTime(QTime::fromString(obj["endTime"].toString(),"h:mm" ));
            video->setLength(QTime::fromString(obj["runTime"].toString(),"h:mm" ));


            //qDebug() << "value: " << value;
        }
        channel->appendVideo(video);
    }
}

void ChannelModelFromJson::parseChannel(Channel *channel, QJsonObject &object)
{
    channel->setNumber(object["number"].toInt() );
    channel->setDescription(object["description"].toString() );
    if(object["type"].toString() == "movie")
        channel->setType(Channel::Type::Movie);
    else if(object["type"].toString() == "tvshow")
        channel->setType(Channel::Type::TvShow);
}
















