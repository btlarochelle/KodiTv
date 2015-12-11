// Qt
#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>


// local
#include "core.h"
#include "backendplugininterface.h"

Core::Core()
{
    qDebug() << "Core ctor";
    loadPlugins();
}


void Core::loadPlugins()
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

