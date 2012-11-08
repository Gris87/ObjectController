#include "localedelegate.h"

#include "../editors/localeeditor.h"
#include "../propertytreewidgetitem.h"

LocaleDelegate::LocaleDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* LocaleDelegate::createEditor(QWidget *aParent) const
{
    return new LocaleEditor(aParent);
}

void LocaleDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    LocaleEditor *aLocaleEditor=(LocaleEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Locale:
            aLocaleEditor->setValue(aItem->firstValue().value<QLocale>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
