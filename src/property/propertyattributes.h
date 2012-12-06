#ifndef PROPERTYATTRIBUTES_H
#define PROPERTYATTRIBUTES_H

#include <QMap>

class PropertyAttributes: public QMap<QString, QString>
{
public:
    explicit PropertyAttributes();

    void fromString(const QString &aString);

    int intValue(const QString &aKey, const int aDefaultValue=0) const;
    double doubleValue(const QString &aKey, const double aDefaultValue=0) const;
};

#endif // PROPERTYATTRIBUTES_H
