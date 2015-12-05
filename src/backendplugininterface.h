#ifndef BACKENDPLUGININTERFACE_H
#define BACKENDPLUGININTERFACE_H

#include <QtCore/qglobal.h>

class BackendPluginInterface
{
public:
    virtual ~BackendPluginInterface() {}

    virtual void DoSomething() const = 0;

};

Q_DECLARE_INTERFACE(BackendPluginInterface, "com.KodiTv.Qt.BackendPluginInterface")


#endif // BACKENDPLUGININTERFACE_H
