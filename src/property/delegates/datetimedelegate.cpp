#include "datetimedelegate.h"

#include <QDateTime>

#include "../editors/datetimeeditor.h"
#include "../propertytreewidgetitem.h"

DateTimeDelegate::DateTimeDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* DateTimeDelegate::createEditor(QWidget *aParent) const
{
    return new DateTimeEditor(aParent);
}

void DateTimeDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    DateTimeEditor *aDateTimeEditor=(DateTimeEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::DateTime:
            aDateTimeEditor->setValue(aItem->firstValue().value<QDateTime>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
