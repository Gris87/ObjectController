#include "easingcurvedelegate.h"

#include <QEasingCurve>

#include "../editors/easingcurveeditor.h"
#include "../propertytreewidgetitem.h"

EasingCurveDelegate::EasingCurveDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* EasingCurveDelegate::createEditor(QWidget *aParent) const
{
    return new EasingCurveEditor(aParent);
}

void EasingCurveDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    EasingCurveEditor *aEasingCurveEditor=(EasingCurveEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::EasingCurve:
            aEasingCurveEditor->setValue(aItem->firstValue().value<QEasingCurve>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
