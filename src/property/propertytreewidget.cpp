#include "propertytreewidget.h"

#include <QKeyEvent>
#include <QApplication>
#include <QPainter>
#include <QHeaderView>

#include "propertytreewidgetitem.h"
#include "objectcontroller.h"

PropertyTreeWidget::PropertyTreeWidget(ObjectController *aController) :
    QTreeWidget(aController)
{
    mController=aController;

    mItemDelegate=new PropertyItemDelegate(this);
    setItemDelegate(mItemDelegate);

    //----------------------------------------------------------------------

    mBoolDelegate        = mController->createBoolDelegate();
    mIntegerDelegate     = mController->createIntegerDelegate();
    mDoubleDelegate      = mController->createDoubleDelegate();
    mCharDelegate        = mController->createCharDelegate();
    mStringListDelegate  = mController->createStringListDelegate();
    mStringDelegate      = mController->createStringDelegate();
    mByteArrayDelegate   = mController->createByteArrayDelegate();
    mBitArrayDelegate    = mController->createBitArrayDelegate();
    mDateDelegate        = mController->createDateDelegate();
    mTimeDelegate        = mController->createTimeDelegate();
    mDateTimeDelegate    = mController->createDateTimeDelegate();
    mLocaleDelegate      = mController->createLocaleDelegate();
    mRectDelegate        = mController->createRectDelegate();
    mRectFDelegate       = mController->createRectFDelegate();
    mSizeDelegate        = mController->createSizeDelegate();
    mSizeFDelegate       = mController->createSizeFDelegate();
    mLineDelegate        = mController->createLineDelegate();
    mLineFDelegate       = mController->createLineFDelegate();
    mPointDelegate       = mController->createPointDelegate();
    mPointFDelegate      = mController->createPointFDelegate();
    mEasingCurveDelegate = mController->createEasingCurveDelegate();
    mFontDelegate        = mController->createFontDelegate();
    mPixmapDelegate      = mController->createPixmapDelegate();
    mBrushDelegate       = mController->createBrushDelegate();
    mColorDelegate       = mController->createColorDelegate();
    mPaletteDelegate     = mController->createPaletteDelegate();
    mIconDelegate        = mController->createIconDelegate();
    mPolygonDelegate     = mController->createPolygonDelegate();
    mRegionDelegate      = mController->createRegionDelegate();
    mCursorDelegate      = mController->createCursorDelegate();
    mSizePolicyDelegate  = mController->createSizePolicyDelegate();
    mKeySequenceDelegate = mController->createKeySequenceDelegate();
    mPenDelegate         = mController->createPenDelegate();
    mTextLengthDelegate  = mController->createTextLengthDelegate();
    mTextFormatDelegate  = mController->createTextFormatDelegate();
    mMatrixDelegate      = mController->createMatrixDelegate();
    mTransformDelegate   = mController->createTransformDelegate();
    mMatrix4x4Delegate   = mController->createMatrix4x4Delegate();

    //----------------------------------------------------------------------

    setIconSize(QSize(18, 18));

    setColumnCount(2);
    setHeaderLabels(QStringList() << tr("Property") << tr("Value"));
    setColumnWidth(0, 200);

    header()->setMovable(false);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void PropertyTreeWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        case Qt::Key_Space:
        {
            PropertyTreeWidgetItem *aItem=(PropertyTreeWidgetItem *)currentItem();

            if (
                aItem
                &&
                (aItem->flags() & Qt::ItemIsEditable)
               )
            {
                event->accept();
                editItem(aItem, 1);

                return;
            }
        }
        break;
    }

    QTreeWidget::keyPressEvent(event);
}

void PropertyTreeWidget::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);

    PropertyTreeWidgetItem* aItem=(PropertyTreeWidgetItem *)itemAt(event->pos());

    if (aItem)
    {
        if (
            event->button()==Qt::LeftButton
            &&
            header()->logicalIndexAt(event->pos().x())==1
            &&
            (aItem->flags() & Qt::ItemIsEditable)
           )
        {
            editItem(aItem, 1);
        }
    }
}

// TODO: Maybe useless. Remove it
/*
void PropertyTreeWidget::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV3 opt=option;

    PropertyTreeWidgetItem* aItem=(PropertyTreeWidgetItem *)itemFromIndex(index);

    if (aItem->parent())
    {
        Property *aProperty;
        PropertyTreeWidgetItem* aCurItem=aItem;

        do
        {
            aProperty=aCurItem->property();

            if (aProperty)
            {
                break;
            }

            aCurItem=(PropertyTreeWidgetItem *)aCurItem->parent();

#ifndef QT_NO_DEBUG
            if (aCurItem==0)
            {
                Q_ASSERT(false);
                break;
            }
#endif
        } while (true);


#ifndef QT_NO_DEBUG
        if (aProperty)
#endif
        {
            QColor aColor=aProperty->backgroundColor();

            if (aColor.isValid())
            {
                if (opt.features & QStyleOptionViewItemV2::Alternate)
                {
                    aColor=aColor.lighter(112);
                }

                painter->fillRect(option.rect, aColor);
            }
        }
    }
    else
    {
        painter->fillRect(option.rect, option.palette.color(QPalette::Dark));
        opt.font.setPointSize(opt.font.pointSize()+2);
        opt.font.setBold(true);
        opt.fontMetrics = QFontMetrics(opt.font);
    }

    QTreeWidget::drawRow(painter, opt, index);



    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    painter->drawLine(option.rect.x(), option.rect.bottom(), option.rect.right(), option.rect.bottom());
    painter->restore();
}
*/

void PropertyTreeWidget::fillByPropertyGroups(QList<PropertyGroup *> aGroups)
{
    clear();

    QList<QTreeWidgetItem *> aTopLevelItems;

    for (int i=0; i<aGroups.length(); ++i)
    {
        PropertyTreeWidgetItem* aTopItem=new PropertyTreeWidgetItem();
        aTopItem->setText(0, aGroups.at(i)->name());



        QList<Property *> aProperties=aGroups.at(i)->properties();

        for (int j=0; j<aProperties.length(); ++j)
        {
            PropertyTreeWidgetItem* aItem=new PropertyTreeWidgetItem(aTopItem);
            aItem->setProperty(aProperties.at(j));
            aItem->setText(0, aProperties.at(j)->name());
            aItem->setFlags(aItem->flags() | Qt::ItemIsEditable);
        }



        aTopLevelItems.append(aTopItem);
    }

    addTopLevelItems(aTopLevelItems);

    for (int i=0; i<aTopLevelItems.length(); ++i)
    {
        aTopLevelItems.at(i)->setExpanded(true);
        aTopLevelItems.at(i)->setFirstColumnSpanned(true);
    }
}

void PropertyTreeWidget::update(const QObjectList &aObjects)
{
    for (int i=0; i<topLevelItemCount(); ++i)
    {
        PropertyTreeWidgetItem *aItem=(PropertyTreeWidgetItem *)topLevelItem(i);

        for (int j=0; j<aItem->childCount(); ++j)
        {
            ((PropertyTreeWidgetItem *)aItem->child(j))->update(aObjects);
        }
    }
}

// -------------------------------------------------------------------------------------

ObjectController* PropertyTreeWidget::controller() const
{
    return mController;
}

CustomDelegate* PropertyTreeWidget::boolDelegate()
{
    return mBoolDelegate;
}

CustomDelegate* PropertyTreeWidget::integerDelegate()
{
    return mIntegerDelegate;
}

CustomDelegate* PropertyTreeWidget::doubleDelegate()
{
    return mDoubleDelegate;
}

CustomDelegate* PropertyTreeWidget::charDelegate()
{
    return mCharDelegate;
}

CustomDelegate* PropertyTreeWidget::stringListDelegate()
{
    return mStringListDelegate;
}

CustomDelegate* PropertyTreeWidget::stringDelegate()
{
    return mStringDelegate;
}

CustomDelegate* PropertyTreeWidget::byteArrayDelegate()
{
    return mByteArrayDelegate;
}

CustomDelegate* PropertyTreeWidget::bitArrayDelegate()
{
    return mBitArrayDelegate;
}

CustomDelegate* PropertyTreeWidget::dateDelegate()
{
    return mDateDelegate;
}

CustomDelegate* PropertyTreeWidget::timeDelegate()
{
    return mTimeDelegate;
}

CustomDelegate* PropertyTreeWidget::dateTimeDelegate()
{
    return mDateTimeDelegate;
}

CustomDelegate* PropertyTreeWidget::localeDelegate()
{
    return mLocaleDelegate;
}

CustomDelegate* PropertyTreeWidget::rectDelegate()
{
    return mRectDelegate;
}

CustomDelegate* PropertyTreeWidget::rectFDelegate()
{
    return mRectFDelegate;
}

CustomDelegate* PropertyTreeWidget::sizeDelegate()
{
    return mSizeDelegate;
}

CustomDelegate* PropertyTreeWidget::sizeFDelegate()
{
    return mSizeFDelegate;
}

CustomDelegate* PropertyTreeWidget::lineDelegate()
{
    return mLineDelegate;
}

CustomDelegate* PropertyTreeWidget::lineFDelegate()
{
    return mLineFDelegate;
}

CustomDelegate* PropertyTreeWidget::pointDelegate()
{
    return mPointDelegate;
}

CustomDelegate* PropertyTreeWidget::pointFDelegate()
{
    return mPointFDelegate;
}

CustomDelegate* PropertyTreeWidget::easingCurveDelegate()
{
    return mEasingCurveDelegate;
}

CustomDelegate* PropertyTreeWidget::fontDelegate()
{
    return mFontDelegate;
}

CustomDelegate* PropertyTreeWidget::pixmapDelegate()
{
    return mPixmapDelegate;
}

CustomDelegate* PropertyTreeWidget::brushDelegate()
{
    return mBrushDelegate;
}

CustomDelegate* PropertyTreeWidget::colorDelegate()
{
    return mColorDelegate;
}

CustomDelegate* PropertyTreeWidget::paletteDelegate()
{
    return mPaletteDelegate;
}

CustomDelegate* PropertyTreeWidget::iconDelegate()
{
    return mIconDelegate;
}

CustomDelegate* PropertyTreeWidget::polygonDelegate()
{
    return mPolygonDelegate;
}

CustomDelegate* PropertyTreeWidget::regionDelegate()
{
    return mRegionDelegate;
}

CustomDelegate* PropertyTreeWidget::cursorDelegate()
{
    return mCursorDelegate;
}

CustomDelegate* PropertyTreeWidget::sizePolicyDelegate()
{
    return mSizePolicyDelegate;
}

CustomDelegate* PropertyTreeWidget::keySequenceDelegate()
{
    return mKeySequenceDelegate;
}

CustomDelegate* PropertyTreeWidget::penDelegate()
{
    return mPenDelegate;
}

CustomDelegate* PropertyTreeWidget::textLengthDelegate()
{
    return mTextLengthDelegate;
}

CustomDelegate* PropertyTreeWidget::textFormatDelegate()
{
    return mTextFormatDelegate;
}

CustomDelegate* PropertyTreeWidget::matrixDelegate()
{
    return mMatrixDelegate;
}

CustomDelegate* PropertyTreeWidget::transformDelegate()
{
    return mTransformDelegate;
}

CustomDelegate* PropertyTreeWidget::matrix4x4Delegate()
{
    return mMatrix4x4Delegate;
}
