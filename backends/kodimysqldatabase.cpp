// Qt
#include <QDebug>

#include "kodimysqldatabase.h"

KodiMysqlDatabase::KodiMysqlDatabase() {}
KodiMysqlDatabase::~KodiMysqlDatabase() {}

void KodiMysqlDatabase::doSomething() const
{
    qDebug() << "KodiMysqlDatabase::doSomething() Called";
}
