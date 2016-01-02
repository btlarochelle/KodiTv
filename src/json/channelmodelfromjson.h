#ifndef CHANNELMODELFROMJSON_H
#define CHANNELMODELFROMJSON_H

#include <QObject>
#include <QJsonDocument>

class ChannelModel;
class Criteria;
class Channel;

class ChannelModelFromJson : public QObject
{
    Q_OBJECT
public:
    ChannelModelFromJson(const QString &file);
    bool parse(ChannelModel &model);
private:
    void parseCriteria(Channel *channel, QJsonObject &object);
    void parseVideos(Channel *channel, QJsonArray &array);
    void parseChannel(Channel *channel, QJsonObject &object);

    QJsonDocument document;
};

#endif




