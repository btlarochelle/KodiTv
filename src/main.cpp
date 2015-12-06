#include <QCoreApplication>

#include "koditv.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    KodiTv kodiTv;
    Q_UNUSED(kodiTv);

    return a.exec();
}

