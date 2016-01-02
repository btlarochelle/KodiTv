#ifndef CHANNELMODEL_H
#define CHANNELMODEL_H

#include <QObject>
#include <QTime>
#include "criteria.h"

class VideoItem
{
public:
    VideoItem() : mTitle("invalid") {}
    QString title() const { return mTitle; }
    QString summary() const { return mSummary; }
    QString file() const { return mFile; }
    QTime startTime() const { return mStartTime; }
    QTime endTime() const { return mEndTime; }
    QTime length() const { return mLength; }
    void setTitle(const QString &title) { mTitle = title; }
    void setSummary(const QString &summary) { mSummary = summary; }
    void setFile(const QString &file) { mFile = file; }
    void setStartTime(const QTime &time) { mStartTime = time; }
    void setEndTime(const QTime &time) { mEndTime = time; }
    void setLength(const QTime &length) { mLength = length; }
private:
    Q_DISABLE_COPY(VideoItem)
    QString mTitle;
    QString mSummary;
    QString mFile;
    QTime mStartTime;
    QTime mEndTime;
    QTime mLength;
};

// **********************************
// **********************************
class Channel
{
public:
    enum class Type {
        TvShow,
        Movie,
        Mixed,
        Null
    };
    Channel() : mType(Type::Null), mNumber(-1), mIsReady(false),
                invalidVideoItem(nullptr)  {}
    Channel(const Type &type, const int &number)
              : mType(type), mNumber(number), mIsReady(false),
                invalidVideoItem(nullptr) {}
    ~Channel() { clearVideos();  if(invalidVideoItem) delete invalidVideoItem;  }

    Type type() const { return mType; }
    int number() const { return mNumber; }
    bool isReady() const { return mIsReady; }
    QString description() const { return mDescription; }
    Criteria& criteria() { return mCriteria; }

    void setType(Type type) { mType = type; }
    void setNumber(int number) { mNumber = number; }
    void setIsReady(bool ready) { mIsReady = ready; }
    void setDescription(const QString &description) { mDescription = description; }
    void setCriteria(const Criteria &criteria) { mCriteria = criteria; }

    void clearVideos() { qDeleteAll(mVideos.begin(), mVideos.end()); mVideos.clear(); }
    void appendVideo(VideoItem *video) { mVideos.append(video); }
    int videoCount() const { return mVideos.count(); }

    void removeVideoAt(const int &index);
    VideoItem* videoAt(const int &index);
private:
    Q_DISABLE_COPY(Channel)
    Type mType;
    int mNumber;
    bool mIsReady;
    QString mDescription;
    Criteria mCriteria;
    QList<VideoItem*> mVideos;
    VideoItem *invalidVideoItem;
};

// **********************************
// **********************************
#include <QAbstractListModel>
#include <QHash>

class ChannelModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        ChannelNumber = Qt::UserRole + 1,
        Title,
        Summary,
        Description
    };
    ChannelModel();
    ~ChannelModel();

    void clear();
    bool isEmpty() const;

    Channel* at(const int &index);
    Channel* findChannelByNumber(const int &number);
    void insert(int row, Channel *channel);
    void append(Channel *channel);
    void removeAt(const int &index);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    Q_DISABLE_COPY(ChannelModel)
    QHash<int, QByteArray> mRoleNames;
    QList<Channel*> mChannels;
    Channel *invalid;

};
#endif






















