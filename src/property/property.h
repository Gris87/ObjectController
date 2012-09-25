#ifndef PROPERTY_H
#define PROPERTY_H

#include <QMetaProperty>

#include <QColor>

class Property
{
public:
    Property(const QMetaProperty &aMetaProperty);

    QString name() const;
    QColor  backgroundColor() const;

protected:
    QMetaProperty mMetaProperty;
    QString       mName;
    QColor        mBackgroundColor;
};

#endif // PROPERTY_H
