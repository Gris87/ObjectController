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

    bool    isModified() const;
    void    setModified(const bool aModified);

protected:
    QMetaProperty mMetaProperty;
    QString       mName;
    QColor        mBackgroundColor;
    bool          mModified;
};

#endif // PROPERTY_H
