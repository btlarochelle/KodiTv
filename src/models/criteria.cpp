// Qt
#include <QDebug>

// local
#include "criteria.h"

//Criteria::Criteria() {}

Criteria::Criteria() : mLimit(50) {}

Criteria::~Criteria() {}

void Criteria::clear()
{
    mColumns.clear();
    mFrom.clear();
    mWhere.clear();
    mAnd.clear();
    mOrderBy.clear();
    mLimit = 0;
}

bool Criteria::isEmpty() const
{
    if(mColumns.isEmpty() && mFrom.isEmpty())
        return true;
    return false;
}

int Criteria::columnCount() const
{
    return mColumns.size();
}

int Criteria::andCount() const
{
    return mAnd.count();
}


bool Criteria::hasWhere() const
{
    return !mWhere.isEmpty();
}

bool Criteria::hasOrderBy() const
{
    return !mOrderBy.isEmpty();
}

// getters
QStringList Criteria::column() const
{
    return mColumns;
}

QString Criteria::from() const
{
    return mFrom;
}

Condition Criteria::where() const
{
    return mWhere;
}

QList<Condition> Criteria::andList() const
{
    return mAnd;
}

int Criteria::limit() const
{
    return mLimit;
}

Condition Criteria::orderBy() const
{
    return mOrderBy;
}

// setters
void Criteria::setFrom(const QString &from)
{
    mFrom = from;
}

void Criteria::setLimit(const int &limit)
{
    mLimit = limit;
}

void Criteria::setOrderBy(const QString &column, const QString &value)
{
    mOrderBy.setColumn(column);
    mOrderBy.setValue(value);
}


// append setters
void Criteria::appendColumn(const QString &column)
{
    mColumns.append(column);
}

void Criteria::addWhere(const QString &column, const QString &operation, const QString &value)
{
    mWhere.setColumn(column);
    mWhere.setOperation(operation);
    mWhere.setValue(value);
}

void Criteria::addAnd(const QString &column, const QString &operation, const QString &value)
{
    Condition condition(column, operation, value);
    mAnd.append(condition);
}

QString Criteria::toString()
{
    QString query;

    query = QString("select ");
    for(int i = 0; i < mColumns.size(); i++) {
        query.append(QString("%1").arg(mColumns.at(i)));
        if(i < mColumns.size() - 1)
            query.append(", ");
    }
    query.append(QString(" from %1").arg(mFrom));
    if(!mWhere.isEmpty()) {
        query.append(QString(" where %1 %2 %3").arg(mWhere.column()).arg(mWhere.operation()).arg(mWhere.value()) );
        if(!mAnd.isEmpty() ) {
            for(int i = 0; i < mAnd.size(); i++ ) {
                query.append(QString(" and %1 %2 %3").arg(mAnd.at(i).column()).arg(mAnd.at(i).operation()).arg(mAnd.at(i).value()) );
            }
        }
    }
    if(!mOrderBy.isEmpty())
        query.append(QString(" order_by %1 %2").arg(mOrderBy.column()).arg(mOrderBy.value()) );

    query.append(QString(" limit %1").arg(mLimit) );


    return query;
}






































