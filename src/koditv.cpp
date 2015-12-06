// Qt
#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>


// local
#include "koditv.h"
#include "backendplugininterface.h"

KodiTv::KodiTv()
{
    qDebug() << "KodiTv ctor";
    loadPlugins();
}


void KodiTv::loadPlugins()
{
    pluginsDir = QDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if(plugin) {
            BackendPluginInterface *tmp = qobject_cast<BackendPluginInterface*>(plugin);
            tmp->doSomething();
            pluginFileNames += fileName;
        }
    }
    qDebug() << "available plugins: " << pluginFileNames;
}

