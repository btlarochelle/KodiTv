// Qt
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

// local
#include "channelmodeltojson.h"
#include "../models/channelmodel.h"
#include "../models/criteria.h"
#include "../include/config.h"

ChannelModelToJson::ChannelModelToJson(const QString &file)
{
    jsonFile.setFileName(file);
    if(!jsonFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << DEBUG_FUNCTION << "failed to open: " << file;
        return;
    }
}

// public
void ChannelModelToJson::write(ChannelModel &model)
{
    QJsonObject rootObject;

    QJsonArray channelsArray;
    for(int i = 0; i < model.rowCount(); i++) {
        Channel *channel = model.at(i);
        QJsonObject arrayObject;

        arrayObject["description"] = channel->description();
        arrayObject["number"] = channel->number();
        if(channel->type() == Channel::Type::TvShow)
            arrayObject["type"] = "tvshow";
        else if(channel->type() == Channel::Type::Movie)
            arrayObject["type"] = "movie";

        if(!channel->criteria().isEmpty() )
            arrayObject["criteria"] = constructCriteriaObject(channel->criteria() );

        if(channel->videoCount() > 0)
            arrayObject["videos"] = constructVideosArray(channel);

        channelsArray.append(arrayObject);
    }
    rootObject["channels"] = channelsArray;
    channelsArray.append(rootObject);
    QJsonDocument document(rootObject);

    jsonFile.write(document.toJson() );
    jsonFile.close();
}

// private
QJsonObject ChannelModelToJson::constructCriteriaObject(Criteria &criteria)
{
    QJsonObject object;
    object["limit"] = criteria.limit();
    if(criteria.hasWhere() ) {
        QJsonArray array;
        for(int i = 0; i < criteria.whereCount(); i++) {
            QJsonObject column;

            QJsonObject obj {
                { criteria.where().at(i).operation(), criteria.where().at(i).value()   }
            };

            column[criteria.where().at(i).column()] = obj;
            array.append(column);
        }
        object["where"] = array;
    }
    return object;
}

QJsonArray ChannelModelToJson::constructVideosArray(Channel *channel)
{
    QJsonArray array;

    QJsonObject object;
    for(int i = 0; i < channel->videoCount(); i++) {
        object["title"] = channel->videoAt(i)->title();
        object["summary"] = channel->videoAt(i)->summary();
        object["file"] = channel->videoAt(i)->file();


        //qDebug() << "time: " << channel->videoAt(i)->startTime().toString( );

        object["startTime"] = channel->videoAt(i)->startTime().toString("h:mm");
        object["endTime"] = channel->videoAt(i)->endTime().toString("h:mm");
        object["runTime"] = channel->videoAt(i)->length().toString("h:mm");


        array.append(object);
    }


    return array;
}


































