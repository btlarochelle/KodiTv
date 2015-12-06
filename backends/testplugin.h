#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include <QtPlugin>

#include "../src/backendplugininterface.h"

class TestPlugin : public QObject, public BackendPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.KodiTv.BackendPluginInterface" )
    Q_INTERFACES(BackendPluginInterface)
public:
    TestPlugin();
    void doSomething() const;
};

#endif // TESTPLUGIN_H
