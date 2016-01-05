// Qt
#include <QDebug>

#include "kodimysqldatabase.h"
#include "querythread.h"
#include "../src/models/channelmodel.h"
#include "../include/config.h"

const QString MovieGenres("MoviesGenres");
const QString TvShowGenres("TvshowsGenres");
const QString MovieByGenre("MovieByGenre");
const QString Movies("Movies");
const QString TvShows("Tvshows");


KodiMysqlDatabase::KodiMysqlDatabase() : mQuerythread(nullptr) {}

KodiMysqlDatabase::KodiMysqlDatabase(Connection connection)
    : mQuerythread(nullptr), mConnection(connection) {}

KodiMysqlDatabase::~KodiMysqlDatabase()
{
    if(mQuerythread)
        delete mQuerythread;
}

void KodiMysqlDatabase::start()
{
    qDebug() << DEBUG_FUNCTION << "entered";
    mQuerythread = new QueryThread();
    //if(mConnection != 0) {
        mQuerythread->setHost(mConnection.host);
        mQuerythread->setUsername(mConnection.username);
        mQuerythread->setPassword(mConnection.password);
        mQuerythread->setDatabaseName(mConnection.databaseName);
        mQuerythread->setConnectionName(mConnection.connectionName);
        mQuerythread->setDriver(mConnection.driver);
        mQuerythread->setPort(mConnection.port);
    //}

    connect(mQuerythread, SIGNAL(progress(QString)),this, SLOT(process(QString)) );
    connect(mQuerythread, SIGNAL(ready(bool) ), this, SLOT(ready(bool) ) );
    connect(mQuerythread, SIGNAL(results(QString,QList<QSqlRecord>,QString)), this, SLOT(slotResults(QString,QList<QSqlRecord>,QString)) );

    mQuerythread->start();
}

void KodiMysqlDatabase::end()
{
    mQuerythread->exit(0);
    mQuerythread->wait();
}

void KodiMysqlDatabase::runQuery(const QString &queryId, const QString &query)
{
    mQuerythread->execute(queryId, query);
}

void KodiMysqlDatabase::getMovieGenres()
{
    QString query;
    query.append("select distinct(name) from genre ");
    query.append("join genre_link on genre.genre_id=genre_link.genre_id ");
    query.append("and genre_link.media_type='movie' ");
    query.append("order by name asc");
    runQuery(MovieGenres, query);
}

void KodiMysqlDatabase::getTvShowGenres()
{
    QString query;
    query.append("select distinct(name) from genre ");
    query.append("join genre_link on genre.genre_id=genre_link.genre_id ");
    query.append("and genre_link.media_type='tvshow' ");
    query.append("order by name asc");
    runQuery(TvShowGenres, query);
}

void KodiMysqlDatabase::getMoviesByGenre(const QString &queryId, const QString &genre)
{
    QString query;
    query.append("select idMovie, c00, c02,");
    query.append("strFileName, strPath, streamdetails.iVideoDuration ");
    query.append("from movie_view ");
    query.append("join genre_link on genre_link.media_id=movie_view.idMovie ");
    query.append("and genre_link.media_type='movie' ");
    query.append("inner join streamdetails on movie_view.idFile = streamdetails.idFile and streamdetails.iStreamType = \"0\"");
    query.append("join genre on genre.genre_id=genre_link.genre_id ");
    query.append( QString("where genre.name like '%1' ").arg(genre) );
    query.append("order by rand() ");
    query.append("limit 10 ");


/*
    query.append("select idMovie, c00, c02, strFileName, strPath from movie_view ");
    query.append("join genre_link on genre_link.media_id=movie_view.idMovie ");
    query.append("and genre_link.media_type='movie' ");
    query.append("join genre on genre.genre_id=genre_link.genre_id ");
    query.append( QString("where genre.name like '%1' ").arg(genre) );
    query.append("order by rand() ");
    query.append("limit 10 ");
*/
    runQuery(queryId, query);
}

void KodiMysqlDatabase::loadModel(ChannelModel *model)
{
    qDebug() << DEBUG_FUNCTION << "entered";
    this->model = model;
    start();
}

void KodiMysqlDatabase::slotResults(const QString &queryId, const QList<QSqlRecord> &records, const QString &resultId)
{
    qDebug() << DEBUG_FUNCTION_SHORT << "entered";
    qDebug() << "queryId: "  << queryId;
    qDebug() << "returned " << records.count() << " records";
    qDebug() << "resultId: " << resultId;

    //foreach (QSqlRecord record, records) {

    int index = 0;
    Q_UNUSED(index);
    if(queryId.startsWith(MovieByGenre) ) {
        QStringList split = queryId.split("_");
        index = split.at(1).toInt() - 1;
    }

    for(int i = 0; i < records.count(); i++ ) {

        if(queryId == MovieGenres) {
            qDebug() << "movie genre: " << records.at(i).value(0).toString();
            //model->addMovieGenre(record.value(0).toString() );
            model->addMovieGenre(records.at(i).value(0).toString() );
        }
        else if(queryId == TvShowGenres) {
            qDebug() << "tvshow genre: " << records.at(i).value(0).toString();
            model->addTvShowGenre(records.at(i).value(0).toString() );
        }
        else if(queryId.startsWith(MovieByGenre) ) {
            qDebug() << "id: " << records.at(i).value(0).toInt() << "title: " << records.at(i).value(1).toString();
            qDebug() << "      file: " << QString("%1%2").arg(records.at(i).value(4).toString()).arg(records.at(i).value(3).toString());
            qDebug() << "      duration: " << records.at(i).value(5).toString();

            //qDebug() << "title: " << records.at(i).value(2).toString();
            VideoItem *video = new VideoItem();
            video->setTitle(records.at(i).value(1).toString() );
            video->setSummary(records.at(i).value(2).toString() );
            //if(!records.at(i).value(3).toString().endsWith('/')) {
            //    video->setFile(QString("%1/%2").arg(records.at(i).value(4).toString() ).arg(records.at(i).value(3).toString() ) );
            //}
            //else {
                video->setFile(QString("%1%2").arg(records.at(i).value(4).toString() ).arg(records.at(i).value(3).toString() ) );
            //}
             model->at(index)->appendVideo(video);
        }
    }
    if(queryId == MovieGenres) {
        //getTvShowGenres();

    }
    else if(queryId == TvShowGenres) {
        //getMoviesByGenre("Action");

    }
    if(queryId == MovieByGenre) {


        //emit finished();
    }



}

void KodiMysqlDatabase::process(QString msg)
{
    qDebug() << DEBUG_FUNCTION << msg;
}

void KodiMysqlDatabase::ready(bool ready)
{
    qDebug() << DEBUG_FUNCTION << "ready: " << ready;
    if(ready) {
        getMovieGenres();
        getTvShowGenres();

        if(model->rowCount() > 0) {
            for(int i = 0; i < model->rowCount(); i++) {
                QString queryId = QString("%1_%2_%3").arg(MovieByGenre)
                                                     .arg(model->at(i)->number())
                                                     .arg(model->at(i)->criteria().where().at(0).value());
                getMoviesByGenre(queryId, model->at(i)->criteria().where().at(0).value());
            }
        }
    }
}






























