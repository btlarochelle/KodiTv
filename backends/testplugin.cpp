// Qt
#include <QDebug>

#include "testplugin.h"

TestPlugin::TestPlugin()
{



}

void TestPlugin::doSomething() const
{
    qDebug() << "do somethign called";
}


