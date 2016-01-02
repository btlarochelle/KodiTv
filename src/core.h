#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDir>
#include <QStringList>


class Core : public QObject
{
    Q_OBJECT
public:
    Core();
    
    void loadPlugins();

private:
    QDir pluginsDir;
    QStringList pluginFileNames;
};




#endif
