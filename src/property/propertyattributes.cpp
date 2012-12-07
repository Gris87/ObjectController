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

bool PropertyAttributes::boolValue(const QString &aKey, const bool aDefaultValue) const
{
    QString aValue=value(aKey);

    if (aValue=="1" || aValue.compare("true", Qt::CaseInsensitive)==0)
    {
        return true;
    }

    if (aValue=="0" || aValue.compare("false", Qt::CaseInsensitive)==0)
    {
        return false;
    }

    return aDefaultValue;
}

int PropertyAttributes::intValue(const QString &aKey, const int aDefaultValue) const
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

double PropertyAttributes::doubleValue(const QString &aKey, const double aDefaultValue) const
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

QString PropertyAttributes::stringValue(const QString &aKey, const QString aDefaultValue) const
{
    QString aValue=value(aKey, aDefaultValue);

    if (aValue.endsWith("\""))
    {
        aValue.remove(aValue.length()-1, 1);
    }

    if (aValue.startsWith("\""))
    {
        aValue.remove(0, 1);
    }

    return aValue;
}

QColor PropertyAttributes::colorValue(const QString &aKey, const QColor aDefaultValue) const
{
    QString aValue=value(aKey, aDefaultValue.name());
    QColor res(aValue);

    if (res.isValid())
    {
        return res;
    }

    return aDefaultValue;
}
