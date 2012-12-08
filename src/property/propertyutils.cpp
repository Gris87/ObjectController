#include "propertyutils.h"

#include <QList>
#include <QMetaEnum>

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

void applyAttributesToPalette(QWidget *aWidget, const PropertyAttributes *aAttributes)
{
    QMetaEnum aMetaEnum=QPalette::staticMetaObject.enumerator(QPalette::staticMetaObject.indexOfEnumerator("ColorRole"));

    QPalette aPalette=aWidget->palette();

    for (int i=0; i<QPalette::NColorRoles; ++i)
    {
        QString aColorName=aMetaEnum.valueToKey(i);
        aColorName[0]=aColorName.at(0).toLower();
        aColorName.append("Color");

        aPalette.setColor((QPalette::ColorRole)i, aAttributes->colorValue(aColorName, aPalette.color((QPalette::ColorRole)i)));
    }

    aWidget->setPalette(aPalette);
}
