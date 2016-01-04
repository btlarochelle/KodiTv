
// local
#include "channelmodel.h"

// channel ******************************
// ***********************************
void Channel::removeVideoAt(const int &index)
{
    if(index > mVideos.count() -1 || index < 0 )
        return;
    delete (mVideos.takeAt(index));
}

VideoItem* Channel::videoAt(const int &index)
{
    if(index > mVideos.count() - 1 || index < 0 ) {
        if(!invalidVideoItem)
            invalidVideoItem = new VideoItem();
        return invalidVideoItem;
    }
    return mVideos.at(index);
}


// channelModel **********************
// ***********************************
ChannelModel::ChannelModel() :
     QAbstractListModel(), invalid(nullptr)
{
    mRoleNames = roleNames();
}

ChannelModel::~ChannelModel()
{
    clear();
    if(invalid)
        delete invalid;
}

void ChannelModel::clear()
{
    qDeleteAll(mChannels.begin(), mChannels.end());
    mChannels.clear();
}

void ChannelModel::clearGenres()
{
    mMovieGenres.clear();
    mTvShowGenres.clear();
}


bool ChannelModel::isEmpty() const
{
    return mChannels.isEmpty();
}

Channel* ChannelModel::at(const int &index)
{
    if(index > mChannels.count() - 1 || index < 0) {
        if(!invalid)
            invalid = new Channel();
        return invalid;
    }
    return (mChannels.at(index));
}

Channel* ChannelModel::findChannelByNumber(const int &number)
{
    if(mChannels.count() < 1) {
        if(!invalid)
            invalid = new Channel();
        return invalid;
    }
    foreach(Channel *channel, mChannels) {
        if(channel->number() == number)
            return channel;
    }
    if(!invalid) invalid = new Channel();
    return invalid;
}

void ChannelModel::insert(int row, Channel *channel)
{
    beginInsertRows(QModelIndex(), row, row);
    mChannels.insert(row, channel);
    endInsertRows();
}

void ChannelModel::append(Channel *channel)
{
    mChannels.append(channel);
}

void ChannelModel::removeAt(const int &index)
{
    if(index > mChannels.count() -1 || index < 0)
        return;
    beginRemoveRows(QModelIndex(), index, index);
    delete (mChannels.takeAt(index));
    //mChannels.removeAt(row);
    endRemoveRows();
}

QStringList ChannelModel::movieGenres() const
{
    return mMovieGenres;
}

QStringList ChannelModel::tvShowGenres() const
{
    return mTvShowGenres;
}

void ChannelModel::addMovieGenre(const QString &genre)
{
    mMovieGenres.append(genre);
}

void ChannelModel::addTvShowGenre(const QString &genre)
{
   mTvShowGenres.append(genre);
}

int ChannelModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mChannels.count();
}

QVariant ChannelModel::data(const QModelIndex &index, int role) const
{

    if(!index.isValid())
        return QVariant();
    if(index.row() < 0 || index.row() > (mChannels.count() - 1))
        return QVariant();

    switch(role) {
    case ChannelNumber:
        return mChannels.at(index.row())->number();
        break;
    case Title:
        break;
    case Summary:
        break;
    case Description:
        return mChannels.at(index.row())->description();
        break;
    default:
        break;
    };
    return QVariant();
}

// protected
QHash<int, QByteArray> ChannelModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ChannelNumber] = "channelNumber";
    roles[Title] = "title";
    roles[Summary] = "summary";
    roles[Description] = "description";

    return roles;
}





