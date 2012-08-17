#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <QWidget>

class ObjectController : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectController(QWidget *parent = 0);

    void clear();

    void setObject(QObject *aObject);
    void setObjects(const QObjectList &aObjects);
    QObjectList objects() const;

protected:
    QObjectList mObjects;
};

#endif // OBJECTCONTROLLER_H
