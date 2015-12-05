// Qt
#include <QDebug>

#include "test2plugin.h"

Test2Plugin::Test2Plugin()
{



}

void Test2Plugin::DoSomething() const
{
    qDebug() << "do somethign  2 called";
}
