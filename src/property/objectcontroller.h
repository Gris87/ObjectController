#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <QWidget>

#include "handleobject.h"
#include "propertytreewidget.h"
#include "delegates/customdelegate.h"

class ObjectController : public QWidget
{
    Q_OBJECT

    friend class HandleObject;
    friend class PropertyTreeWidget;

public:
    explicit ObjectController(QWidget *parent = 0);

    void invalidate();
    void update();
    void reset();
    void clear();

    void setObject(QObject *aObject);
    void setObjects(const QObjectList &aObjects);
    QObjectList objects() const;

protected:
    typedef QMap<QObject*, HandleObject*> HandledObjects;

    PropertyTreeWidget* mTreeWidget;
    QObjectList         mObjects;
    HandledObjects      mHandledObjects;

    virtual bool filterClass(QString &aClassName);
    virtual bool filterProperty(const QMetaObject *aMetaObject, QString aMetaPropertyName);
    virtual void propertyAdded(const QMetaObject *aMetaObject, Property *aProperty);
    virtual CustomDelegate* createBoolDelegate();
    virtual CustomDelegate* createIntegerDelegate();
    virtual CustomDelegate* createDoubleDelegate();
};

#endif // OBJECTCONTROLLER_H
