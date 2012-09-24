#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <QWidget>

#include <QTreeWidget>

#include "handleobject.h"

class ObjectController : public QWidget
{
    Q_OBJECT
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

    QTreeWidget*   mTreeWidget;
    QObjectList    mObjects;
    HandledObjects mHandledObjects;
};

#endif // OBJECTCONTROLLER_H
