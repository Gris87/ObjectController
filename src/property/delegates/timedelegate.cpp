#include "timedelegate.h"

#include <QTime>

#include "../editors/timeeditor.h"
#include "../propertytreewidgetitem.h"

TimeDelegate::TimeDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* TimeDelegate::createEditor(QWidget *aParent) const
{
    return new TimeEditor(aParent);
}

void TimeDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    TimeEditor *aTimeEditor=(TimeEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Time:
            aTimeEditor->setValue(aItem->firstValue().toTime());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
