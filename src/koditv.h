#ifndef KODITV_H
#define KODITV_H

#include <QObject>
#include <QDir>
#include <QStringList>


class KodiTv : public QObject
{
    Q_OBJECT
public:
    KodiTv();
    
    void loadPlugins();

private:
    QDir pluginsDir;
    QStringList pluginFileNames;

};






#endif
