#include "propertyutils.h"

#include <QList>

QList<double> *decimals=0;

QString doubleToString(double aValue, int aDecimals)
{
    if (aDecimals<0 || aDecimals>6)
    {
        return QString::number(aValue);
    }

    if (decimals==0)
    {
        decimals=new QList<double>();

        decimals->append(1);
        decimals->append(10);
        decimals->append(100);
        decimals->append(1000);
        decimals->append(10000);
        decimals->append(100000);
        decimals->append(1000000);
    }

    double aMultiplier=decimals->at(aDecimals);

    return QString::number(qRound(aValue*aMultiplier)/aMultiplier);
}
