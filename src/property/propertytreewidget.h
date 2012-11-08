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
    CustomDelegate*       stringListDelegate();
    CustomDelegate*       stringDelegate();
    CustomDelegate*       byteArrayDelegate();
    CustomDelegate*       bitArrayDelegate();
    CustomDelegate*       dateDelegate();
    CustomDelegate*       timeDelegate();
    CustomDelegate*       dateTimeDelegate();
    CustomDelegate*       localeDelegate();
    CustomDelegate*       rectDelegate();
    CustomDelegate*       rectFDelegate();
    CustomDelegate*       sizeDelegate();
    CustomDelegate*       sizeFDelegate();
    CustomDelegate*       lineDelegate();
    CustomDelegate*       lineFDelegate();
    CustomDelegate*       pointDelegate();
    CustomDelegate*       pointFDelegate();
    CustomDelegate*       easingCurveDelegate();
    CustomDelegate*       fontDelegate();
    CustomDelegate*       pixmapDelegate();
    CustomDelegate*       brushDelegate();
    CustomDelegate*       colorDelegate();
    CustomDelegate*       paletteDelegate();

protected:
    ObjectController     *mController;
    PropertyItemDelegate *mItemDelegate;

    CustomDelegate       *mBoolDelegate;
    CustomDelegate       *mIntegerDelegate;
    CustomDelegate       *mDoubleDelegate;
    CustomDelegate       *mCharDelegate;
    CustomDelegate       *mStringListDelegate;
    CustomDelegate       *mStringDelegate;
    CustomDelegate       *mByteArrayDelegate;
    CustomDelegate       *mBitArrayDelegate;
    CustomDelegate       *mDateDelegate;
    CustomDelegate       *mTimeDelegate;
    CustomDelegate       *mDateTimeDelegate;
    CustomDelegate       *mLocaleDelegate;
    CustomDelegate       *mRectDelegate;
    CustomDelegate       *mRectFDelegate;
    CustomDelegate       *mSizeDelegate;
    CustomDelegate       *mSizeFDelegate;
    CustomDelegate       *mLineDelegate;
    CustomDelegate       *mLineFDelegate;
    CustomDelegate       *mPointDelegate;
    CustomDelegate       *mPointFDelegate;
    CustomDelegate       *mEasingCurveDelegate;
    CustomDelegate       *mFontDelegate;
    CustomDelegate       *mPixmapDelegate;
    CustomDelegate       *mBrushDelegate;
    CustomDelegate       *mColorDelegate;
    CustomDelegate       *mPaletteDelegate;

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    // TODO: Maybe useless. Remove it
    //void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // PROPERTYTREEWIDGET_H
