#include "datedelegate.h"

#include <QDate>

#include "../editors/dateeditor.h"
#include "../propertytreewidgetitem.h"

DateDelegate::DateDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* DateDelegate::createEditor(QWidget *aParent) const
{
    return new DateEditor(aParent);
}

void DateDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    DateEditor *aDateEditor=(DateEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Date:
            aDateEditor->setValue(aItem->firstValue().value<QDate>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
