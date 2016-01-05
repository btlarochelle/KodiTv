// Qt
#include <QDebug>

// local
#include "criteria.h"

//Criteria::Criteria() {}

Criteria::Criteria() : mLimit(10) {}

Criteria::~Criteria() {}

void Criteria::clear()
{
    mWhere.clear();
    mLimit = 0;
}

bool Criteria::isEmpty() const
{
    if(mWhere.isEmpty() || mLimit == 0)
        return true;
    return false;
}

bool Criteria::hasWhere() const
{
    return !mWhere.isEmpty();
}

int Criteria::whereCount() const
{
    return mWhere.count();
}

// getters
QList<Condition> Criteria::where() const
{
    return mWhere;
}

int Criteria::limit() const
{
    return mLimit;
}

// setters
void Criteria::setLimit(const int &limit)
{
    mLimit = limit;
}

// append setters
void Criteria::addWhere(const QString &column, const QString &operation, const QString &value)
{
    Condition condition(column, operation, value);
    mWhere.append(condition);
}

QString Criteria::toString()
{
    QString query;
    if(!mWhere.isEmpty()) {
        for(int i = 0; i < mWhere.size(); i++) {
            if(i == 0)
                query.append(QString("where %1 %2 %3").arg(mWhere.at(i).column()).arg(mWhere.at(i).operation()).arg(mWhere.at(i).value()) );
            else if(i > 0)
                query.append(QString(" and %1 %2 %3").arg(mWhere.at(i).column()).arg(mWhere.at(i).operation()).arg(mWhere.at(i).value()) );
        }
    }
    query.append(QString(" limit %1").arg(mLimit) );
    return query;
}






































