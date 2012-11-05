#include "stringdelegate.h"

#include <QUrl>
#include <QRegExp>

#include "../editors/stringeditor.h"
#include "../propertytreewidgetitem.h"

StringDelegate::StringDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* StringDelegate::createEditor(QWidget *aParent) const
{
    return new StringEditor(aParent);
}

void StringDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    StringEditor *aStringEditor=(StringEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::String:
            aStringEditor->setValue(aItem->firstValue().value<QString>());
        break;
        case QVariant::Url:
            aStringEditor->setValue(aItem->firstValue().value<QUrl>());
        break;
        case QVariant::RegExp:
            aStringEditor->setValue(aItem->firstValue().value<QRegExp>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
