// Qt
#include <QDebug>

#include "testplugin.h"

TestPlugin::TestPlugin()
{



}

void TestPlugin::DoSomething() const
{
    qDebug() << "do somethign called";
}


