#include "stringdelegate.h"

#include <QUrl>
#include <QRegExp>

#include "../editors/stringeditor.h"
#include "../propertytreewidgetitem.h"
#include "../propertytreewidget.h"
#include "../objectcontroller.h"

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

    QStringList aValues;
    Property *aTopProperty=aItem->topProperty();

    bool good=aTopProperty
              &&
              ((PropertyTreeWidget *)aItem->treeWidget())->controller()->objects().length()>0;

    if (good)
    {
        const QMetaObject *aMetaObject=aTopProperty->propertyObject();

        int index=aMetaObject->indexOfMethod("valuesForProperty(QString,QStringList&)");
        good=(index>=0);

        if (good)
        {
            bool filtered;

            good=aMetaObject->method(index).invoke(
                                                   ((PropertyTreeWidget *)aItem->treeWidget())->controller()->objects().at(0),
                                                   Qt::DirectConnection,
                                                   Q_RETURN_ARG(bool, filtered),
                                                   Q_ARG(QString, aTopProperty->name()),
                                                   Q_ARG(QStringList, aValues)
                                                  );

            good=(good && filtered);
        }
    }

    if (good)
    {
        switch (aItem->firstValue().type())
        {
            case QVariant::String:
                aStringEditor->setValue(aValues, aItem->firstValue().value<QString>());
            break;
            case QVariant::Url:
                aStringEditor->setValue(aValues, aItem->firstValue().value<QUrl>());
            break;
            case QVariant::RegExp:
                aStringEditor->setValue(aValues, aItem->firstValue().value<QRegExp>());
            break;
            default:
                Q_ASSERT(false); // Impossible
            break;
        }
    }
    else
    {
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
}
