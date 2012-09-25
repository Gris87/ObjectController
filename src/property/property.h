#ifndef PROPERTY_H
#define PROPERTY_H

#include <QMetaProperty>

#include <QColor>

class Property
{
public:
    Property(const QMetaProperty aProperty);

    QString name() const;
    QColor  backgroundColor() const;

protected:
    QString mName;
    QColor  mBackgroundColor;
};

#endif // PROPERTY_H
