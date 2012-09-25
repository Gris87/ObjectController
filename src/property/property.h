#ifndef PROPERTY_H
#define PROPERTY_H

#include <QMetaProperty>

#include <QColor>

class Property
{
public:
    Property(const QMetaProperty &aMetaProperty);

    bool equals(const Property *aProperty);

    QVariant read(const QObjectList &aObjects);
    void write(const QObjectList &aObjects, const QVariant &aValue);

    QString name() const;
    QColor  backgroundColor() const;

protected:
    QMetaProperty mMetaProperty;
    QString       mName;
    QColor        mBackgroundColor;
};

#endif // PROPERTY_H
