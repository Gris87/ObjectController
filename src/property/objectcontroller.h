#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <QWidget>

#include <QVBoxLayout>
#include <QTreeWidget>

#include <QStack>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>

class ObjectController : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectController(QWidget *parent = 0);

    void invalidate();
    void clear();

    void setObject(QObject *aObject);
    void setObjects(const QObjectList &aObjects);
    QObjectList objects() const;

    void setRootIsDecorated(bool aDecorated);
    bool rootIsDecorated();

protected:
    QObjectList  mObjects;
    QTreeWidget* mTreeWidget;
};

#endif // OBJECTCONTROLLER_H
