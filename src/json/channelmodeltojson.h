#ifndef CHANNELMODELTOJSON_H
#define CHANNELMODELTOJSON_H

#include <QString>
#include <QJsonDocument>
#include <QFile>

class ChannelModel;
class Channel;
class Criteria;

class ChannelModelToJson
{
public:
    ChannelModelToJson(const QString &file);

    void write(ChannelModel &model);
private:
    QJsonObject constructCriteriaObject(Criteria &criteria);
    QJsonArray constructVideosArray(Channel *channel);
    QFile jsonFile;
};


#endif



