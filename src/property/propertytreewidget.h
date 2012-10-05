#ifndef PROPERTYTREEWIDGET_H
#define PROPERTYTREEWIDGET_H

#include <QTreeWidget>

#include "propertygroup.h"
#include "propertyitemdelegate.h"

#include "delegates/customdelegate.h"

class ObjectController;

class PropertyTreeWidget : public QTreeWidget
{
    Q_OBJECT

    friend class PropertyItemDelegate;

public:
    explicit PropertyTreeWidget(ObjectController *aController);

    void fillByPropertyGroups(QList<PropertyGroup *> aGroups);
    void update(const QObjectList &aObjects);

    ObjectController*     controller() const;

    CustomDelegate*       boolDelegate();
    CustomDelegate*       integerDelegate();
    CustomDelegate*       doubleDelegate();
    CustomDelegate*       charDelegate();
    CustomDelegate*       stringDelegate();
    CustomDelegate*       byteArrayDelegate();
    CustomDelegate*       bitArrayDelegate();

protected:
    ObjectController     *mController;
    PropertyItemDelegate *mItemDelegate;

    CustomDelegate       *mBoolDelegate;
    CustomDelegate       *mIntegerDelegate;
    CustomDelegate       *mDoubleDelegate;
    CustomDelegate       *mCharDelegate;
    CustomDelegate       *mStringDelegate;
    CustomDelegate       *mByteArrayDelegate;
    CustomDelegate       *mBitArrayDelegate;

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    // TODO: Maybe useless. Remove it
    //void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // PROPERTYTREEWIDGET_H
