#include "propertyitemdelegate.h"

#include <QPainter>
#include <QApplication>

#include "propertytreewidget.h"
#include "propertytreewidgetitem.h"

PropertyItemDelegate::PropertyItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void PropertyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    PropertyTreeWidget*     aTreeWidget = (PropertyTreeWidget *)parent();
    PropertyTreeWidgetItem* aItem       = (PropertyTreeWidgetItem *)aTreeWidget->itemFromIndex(index);

    QStyleOptionViewItemV3 opt = option;

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

            if (index.column()==0 && aItem->isModified())
            {
                opt.font.setBold(true);
                opt.fontMetrics = QFontMetrics(opt.font);
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

    opt.state&=~QStyle::State_HasFocus;

    QItemDelegate::paint(painter, opt, index);



    opt.palette.setCurrentColorGroup(QPalette::Active);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));

    if (index.column()<1 && !aItem->isFirstColumnSpanned())
    {
        int right=(option.direction==Qt::LeftToRight) ? option.rect.right() : option.rect.left();
        painter->drawLine(right, option.rect.y(), right, option.rect.bottom());
    }

    painter->drawLine(0, option.rect.bottom(), option.rect.right(), option.rect.bottom());
    painter->restore();
}

QSize PropertyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + QSize(6, 6);
}
