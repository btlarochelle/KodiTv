// Qt
#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>

// system

// local
#include "koditv.h"


KodiTv::KodiTv()
{
    qDebug() << "farts";
    loadPlugins();
}


void KodiTv::loadPlugins()
{
    pluginsDir = QDir(qApp->applicationDirPath());

    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {

            pluginFileNames += fileName;
        }
    }

    qDebug() << pluginFileNames;
}

