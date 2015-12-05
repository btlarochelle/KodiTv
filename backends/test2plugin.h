#ifndef TEST2PLUGIN_H
#define TEST2PLUGIN_H

#include <QtPlugin>

#include "../src/backendplugininterface.h"

class Test2Plugin : public QObject, public BackendPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.KodiTv.BackendPluginInterface" )
    Q_INTERFACES(BackendPluginInterface)
public:
    Test2Plugin();
    void DoSomething() const;
};

#endif // TEST2PLUGIN_H
