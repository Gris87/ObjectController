#ifndef PROPERTYATTRIBUTES_H
#define PROPERTYATTRIBUTES_H

#include <QMap>
#include <QString>
#include <QColor>

class PropertyAttributes: public QMap<QString, QString>
{
public:
    explicit PropertyAttributes();

    void fromString(const QString &aString);

    bool boolValue(const QString &aKey, const bool aDefaultValue=false) const;
    int intValue(const QString &aKey, const int aDefaultValue=0) const;
    double doubleValue(const QString &aKey, const double aDefaultValue=0) const;
    QString stringValue(const QString &aKey, const QString aDefaultValue=QString()) const;
    QColor colorValue(const QString &aKey, const QColor aDefaultValue=QColor()) const;
};

#endif // PROPERTYATTRIBUTES_H
