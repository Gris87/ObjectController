#include "propertyitemdelegate.h"

#include <QPainter>
#include <QApplication>

#include "propertytreewidget.h"
#include "propertytreewidgetitem.h"

#include "editors/defaulteditor.h"

PropertyItemDelegate::PropertyItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget* PropertyItemDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &/*aOption*/, const QModelIndex &aIndex) const
{
    PropertyTreeWidget*     aTreeWidget = (PropertyTreeWidget *)parent();
    PropertyTreeWidgetItem* aItem       = (PropertyTreeWidgetItem *)aTreeWidget->itemFromIndex(aIndex);

    CustomEditor *aCustomEditor=0;

    if (aItem->delegate())
    {
        aCustomEditor=aItem->delegate()->createEditor(aParent);
        aItem->delegate()->setEditorData(aCustomEditor, aItem);
    }
    else
    {
        DefaultEditor *aDefaultEditor=new DefaultEditor(aParent);

        Property *aProperty=aItem->property();

        if (aProperty)
        {
            aDefaultEditor->setValue(aProperty->valueText(aItem->firstValue(), aItem));
        }
        else
        {
            aDefaultEditor->setValue(aItem->text(1));
        }

        aCustomEditor=aDefaultEditor;
    }

    aCustomEditor->setIcon(aItem->icon(1));

    Property *aTopProperty=aItem->topProperty();

    if (aTopProperty)
    {
        aCustomEditor->handleAttributes(aTopProperty->attributes());
    }

    connect(aCustomEditor, SIGNAL(valueChanged(QVariant)), aItem->itemConnector(), SIGNAL(valueChanged(QVariant)));

    return aCustomEditor;
}

void PropertyItemDelegate::paint(QPainter *aPainter, const QStyleOptionViewItem &aOption, const QModelIndex &aIndex) const
{
    PropertyTreeWidget*     aTreeWidget = (PropertyTreeWidget *)parent();
    PropertyTreeWidgetItem* aItem       = (PropertyTreeWidgetItem *)aTreeWidget->itemFromIndex(aIndex);

    QStyleOptionViewItemV3 opt = aOption;

    if (aItem->parent())
    {
        Property *aProperty=aItem->topProperty();

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

                aPainter->fillRect(aOption.rect, aColor);
            }

            if (aItem->isModified())
            {
                opt.font.setBold(true);
                opt.fontMetrics = QFontMetrics(opt.font);
            }

            if (!aProperty->isWriteable())
            {
                QColor aTextColor=aOption.palette.color(QPalette::Text);

                int r=qMin(aTextColor.red()+((255-aTextColor.red())>>1), 255);
                int g=qMin(aTextColor.green()+((255-aTextColor.green())>>1), 255);
                int b=qMin(aTextColor.blue()+((255-aTextColor.blue())>>1), 255);

                aTextColor.setRgb(r, g, b);

                opt.palette.setColor(QPalette::Text, aTextColor);
            }
        }
    }
    else
    {
        aPainter->fillRect(aOption.rect, aOption.palette.color(QPalette::Dark));
        opt.font.setPointSize(opt.font.pointSize());
        opt.font.setBold(true);
        opt.fontMetrics = QFontMetrics(opt.font);
    }

    opt.state&=~QStyle::State_HasFocus;

    QItemDelegate::paint(aPainter, opt, aIndex);



    opt.palette.setCurrentColorGroup(QPalette::Active);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    aPainter->save();
    aPainter->setPen(QPen(color));

    if (aIndex.column()<1 && !aItem->isFirstColumnSpanned())
    {
        int right=(aOption.direction==Qt::LeftToRight) ? aOption.rect.right() : aOption.rect.left();
        aPainter->drawLine(right, aOption.rect.y(), right, aOption.rect.bottom());
    }

    aPainter->drawLine(0, aOption.rect.bottom(), aOption.rect.right(), aOption.rect.bottom());
    aPainter->restore();
}

void PropertyItemDelegate::setEditorData(QWidget * /*aEditor*/, const QModelIndex &/*aIndex*/) const
{
}

void PropertyItemDelegate::setModelData(QWidget * /*aEditor*/, QAbstractItemModel * /*aModel*/, const QModelIndex &/*aIndex*/) const
{
}

QSize PropertyItemDelegate::sizeHint(const QStyleOptionViewItem &aOption, const QModelIndex &aIndex) const
{
    return QItemDelegate::sizeHint(aOption, aIndex) + QSize(6, 6);
}

void PropertyItemDelegate::updateEditorGeometry(QWidget *aEditor, const QStyleOptionViewItem &aOption, const QModelIndex &/*aIndex*/) const
{
    aEditor->setGeometry(aOption.rect);
}
