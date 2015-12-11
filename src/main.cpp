#include <QCoreApplication>

#include "core.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Core core;
    Q_UNUSED(core);

    return a.exec();
}

