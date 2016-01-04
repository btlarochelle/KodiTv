// Qt
#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>


// local
#include "core.h"
#include "../include/backendplugininterface.h"
#include "../include/config.h"

Core::Core()
{
    qDebug() << DEBUG_FUNCTION << "Core ctor";
    loadPlugins();
}


void Core::loadPlugins()
{
    qDebug() << DEBUG_FUNCTION << "entered";
    pluginsDir = QDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if(plugin) {
            BackendPluginInterface *tmp = qobject_cast<BackendPluginInterface*>(plugin);
            Q_UNUSED(tmp);
            //tmp->doSomething();
            pluginFileNames += fileName;
        }
    }
    qDebug() << DEBUG_FUNCTION << "available plugins: " << pluginFileNames;
}

