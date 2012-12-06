#include "propertyattributes.h"

#include <QStringList>

PropertyAttributes::PropertyAttributes() :
    QMap<QString, QString>()
{
}

void PropertyAttributes::fromString(const QString &aString)
{
    clear();

    QStringList aAttributes=aString.split(";");

    for (int i=0; i<aAttributes.length(); ++i)
    {
        QStringList aOnePair=aAttributes.at(i).split(":");

        if (aOnePair.length()>=2)
        {
            QString aValue=aAttributes.at(i).mid(aOnePair.at(0).length()+1);
            insert(aOnePair.at(0).trimmed(), aValue.trimmed());
        }
    }
}

int PropertyAttributes::intValue(const QString &aKey, const int aDefaultValue)
{
    QString aValue=value(aKey);

    bool ok;

    int res=aValue.toInt(&ok);

    if (ok)
    {
        return res;
    }

    return aDefaultValue;
}

double PropertyAttributes::doubleValue(const QString &aKey, const double aDefaultValue)
{
    QString aValue=value(aKey);

    bool ok;

    double res=aValue.toDouble(&ok);

    if (ok)
    {
        return res;
    }

    return aDefaultValue;
}
