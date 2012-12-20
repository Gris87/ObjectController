#include "propertyutils.h"

#include <QApplication>
#include <QList>

QString enumToString(const QMetaEnum &aMetaEnum, const int &aValue)
{
    QString res=qApp->translate("Property", "[No enumeration value]");

    for (int i=0; i<aMetaEnum.keyCount(); ++i)
    {
        if (aMetaEnum.value(i)==aValue)
        {
            res=QString::fromLatin1(aMetaEnum.key(i));
            break;
        }
    }

    return res;
}

QString flagsToString(const QMetaEnum &aMetaEnum, const int &aValue)
{
    QString res="[";

    for (int i=0; i<aMetaEnum.keyCount(); ++i)
    {
        int aFlag=aMetaEnum.value(i);

        if (((aValue & aFlag)==aFlag) && (aFlag!=0 || aValue==0))
        {
            bool good=true;

            while (aFlag)
            {
                if (aFlag & 1)
                {
                    good=(aFlag==1);
                    break;
                }

                aFlag>>=1;
            }

            if (good)
            {
                if (res.length()>1)
                {
                    res.append(", ");
                }

                res.append(QString::fromLatin1(aMetaEnum.key(i)));
            }
        }
    }

    res.append("]");

    return res;
}

QString boolToString(const bool &aValue)
{
    return aValue ? "true" : "false";
}

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
