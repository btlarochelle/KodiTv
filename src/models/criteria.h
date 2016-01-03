#ifndef CRITERIA_H
#define CRITERIA_H

#include <QStringList>
#include <QMap>

class Condition
{
public:
    Condition() {}
    Condition(const QString &column, const QString &operation, const QString &value)
        : mColumn(column), mOperation(operation), mValue(value) {}
    void clear() { mColumn.clear(); mOperation.clear(); mValue.clear(); }
    bool isEmpty() const { return ((mColumn.size() > 0 || mOperation.size() > 0 || mValue.size() > 0) ? false : true); }
    QString column() const { return mColumn; }
    QString operation() const { return mOperation; }
    QString value() const { return mValue; }
    void setColumn(const QString &column) { mColumn = column; }
    void setOperation(const QString &operation) { mOperation = operation; }
    void setValue(const QString &value) { mValue = value; }
private:
    QString mColumn;
    QString mOperation;
    QString mValue;
};


class Criteria
{
public:
    Criteria();
    ~Criteria();
    void clear();
    bool isEmpty() const;
    bool hasWhere() const;
    int whereCount() const;

    // getters
    QList<Condition> where() const;
    int limit() const;
    // setters
    void setLimit(const int &limit);
    void addWhere(const QString &column, const QString &operation, const QString &value);

    QString toString();
private:
    QList<Condition> mWhere;
    int mLimit;
};



#endif



