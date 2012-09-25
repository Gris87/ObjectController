#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <QWidget>

#include "handleobject.h"
#include "propertytreewidget.h"

class ObjectController : public QWidget
{
    Q_OBJECT

    friend class HandleObject;

public:
    explicit ObjectController(QWidget *parent = 0);

    void invalidate();
    void reset();
    void clear();

    void setObject(QObject *aObject);
    void setObjects(const QObjectList &aObjects);
    QObjectList objects() const;

    void setRootIsDecorated(bool aDecorated);
    bool rootIsDecorated();

protected:
    typedef QMap<QObject*, HandleObject*> HandledObjects;

    PropertyTreeWidget* mTreeWidget;
    QObjectList         mObjects;
    HandledObjects      mHandledObjects;

    virtual bool filterClass(QString &aClassName);
    virtual bool filterProperty(const QMetaObject *aMetaObject, QString aMetaPropertyName);
    virtual void propertyAdded(const QMetaObject *aMetaObject, Property *aProperty);
};

#endif // OBJECTCONTROLLER_H
