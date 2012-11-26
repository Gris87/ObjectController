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

    void setIgnoreEmptyClass(bool aValue);
    bool ignoreEmptyClass() const;

    void setObject(QObject *aObject);
    void setObjects(const QObjectList &aObjects);
    QObjectList objects() const;

protected:
    typedef QMap<QObject*, HandleObject*> HandledObjects;

    PropertyTreeWidget* mTreeWidget;
    bool                mIgnoreEmptyClass;
    QObjectList         mObjects;
    HandledObjects      mHandledObjects;

    virtual bool filterClass(QString &aClassName);
    virtual bool filterProperty(const QMetaObject *aMetaObject, QString aMetaPropertyName);
    virtual void propertyAdded(const QMetaObject *aMetaObject, Property *aProperty);

    virtual CustomDelegate* createEnumDelegate();
    virtual CustomDelegate* createBoolDelegate();
    virtual CustomDelegate* createIntegerDelegate();
    virtual CustomDelegate* createDoubleDelegate();
    virtual CustomDelegate* createCharDelegate();
    virtual CustomDelegate* createStringListDelegate();
    virtual CustomDelegate* createStringDelegate();
    virtual CustomDelegate* createByteArrayDelegate();
    virtual CustomDelegate* createBitArrayDelegate();
    virtual CustomDelegate* createDateDelegate();
    virtual CustomDelegate* createTimeDelegate();
    virtual CustomDelegate* createDateTimeDelegate();
    virtual CustomDelegate* createLocaleDelegate();
    virtual CustomDelegate* createRectDelegate();
    virtual CustomDelegate* createRectFDelegate();
    virtual CustomDelegate* createSizeDelegate();
    virtual CustomDelegate* createSizeFDelegate();
    virtual CustomDelegate* createLineDelegate();
    virtual CustomDelegate* createLineFDelegate();
    virtual CustomDelegate* createPointDelegate();
    virtual CustomDelegate* createPointFDelegate();
    virtual CustomDelegate* createEasingCurveDelegate();
    virtual CustomDelegate* createFontDelegate();
    virtual CustomDelegate* createPixmapDelegate();
    virtual CustomDelegate* createBrushDelegate();
    virtual CustomDelegate* createColorDelegate();
    virtual CustomDelegate* createPaletteDelegate();
    virtual CustomDelegate* createIconDelegate();
    virtual CustomDelegate* createPolygonDelegate();
    virtual CustomDelegate* createRegionDelegate();
    virtual CustomDelegate* createCursorDelegate();
    virtual CustomDelegate* createSizePolicyDelegate();
    virtual CustomDelegate* createKeySequenceDelegate();
    virtual CustomDelegate* createPenDelegate();
    virtual CustomDelegate* createTextLengthDelegate();
    virtual CustomDelegate* createTextFormatDelegate();
    virtual CustomDelegate* createMatrixDelegate();
    virtual CustomDelegate* createTransformDelegate();
    virtual CustomDelegate* createMatrix4x4Delegate();
    virtual CustomDelegate* createVector2DDelegate();
    virtual CustomDelegate* createVector3DDelegate();
    virtual CustomDelegate* createVector4DDelegate();
    virtual CustomDelegate* createQuaternionDelegate();

private slots:
    void valueChangedSlot(const QVariant &aNewValue);

signals:
    void valueChanged(Property *aProperty, const QVariant &aValue);
};

#endif // OBJECTCONTROLLER_H
