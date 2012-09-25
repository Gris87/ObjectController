#include "propertytreewidget.h"

#include <QKeyEvent>
#include <QApplication>
#include <QPainter>
#include <QHeaderView>

#include "propertytreewidgetitem.h"

PropertyTreeWidget::PropertyTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    mItemDelegate=new PropertyItemDelegate(this);
    setItemDelegate(mItemDelegate);

    setIconSize(QSize(18, 18));

    setColumnCount(2);
    setHeaderLabels(QStringList() << tr("Property") << tr("Value"));
    setColumnWidth(0, 200);

    header()->setMovable(false);

    setEditTriggers(QAbstractItemView::EditKeyPressed);
}

void PropertyTreeWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        case Qt::Key_Space:
        {
            QTreeWidgetItem *aItem=currentItem();

            if (
                aItem
                &&
                (
                 (aItem->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled)
                )
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
}

void PropertyTreeWidget::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV3 opt=option;

    PropertyTreeWidgetItem* aItem=(PropertyTreeWidgetItem*)itemFromIndex(index);

    if (aItem->property())
    {
        QColor aColor=aItem->property()->backgroundColor();

        if (aColor.isValid())
        {
            painter->fillRect(option.rect, aColor);
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
    painter->drawLine(opt.rect.x(), opt.rect.bottom(), opt.rect.right(), opt.rect.bottom());
    painter->restore();
}

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
        QTreeWidgetItem *aItem=topLevelItem(i);

        for (int j=0; j<aItem->childCount(); ++j)
        {
            ((PropertyTreeWidgetItem *)aItem->child(j))->update(aObjects);
        }
    }
}
