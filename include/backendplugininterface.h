#ifndef BACKENDPLUGININTERFACE_H
#define BACKENDPLUGININTERFACE_H

#include <QtCore/qglobal.h>

class ChannelModel;

class BackendPluginInterface
{
public:
    virtual ~BackendPluginInterface() {}

    virtual void loadModel(ChannelModel *model) = 0;

};

Q_DECLARE_INTERFACE(BackendPluginInterface, "com.KodiTv.Qt.BackendPluginInterface")


#endif // BACKENDPLUGININTERFACE_H
