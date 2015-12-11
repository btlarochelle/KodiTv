#ifndef KODIMYSQLDATABASE_H
#define KODIMYSQLDATABASE_H

#include <QtPlugin>
#include "../src/backendplugininterface.h"


class KodiMysqlDatabase : public QObject, public BackendPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.KodiTv.BackendPluginInterface" )
    Q_INTERFACES(BackendPluginInterface)
public:
    KodiMysqlDatabase();
    ~KodiMysqlDatabase();
    void doSomething() const;

};

#endif


