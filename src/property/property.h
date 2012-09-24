#ifndef PROPERTY_H
#define PROPERTY_H

#include <QMetaProperty>

class Property
{
public:
    Property(const QMetaProperty aProperty);

    QString name() const;

protected:
    QString mName;
};

#endif // PROPERTY_H
