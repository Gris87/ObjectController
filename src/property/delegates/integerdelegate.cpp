#include "integerdelegate.h"

#include "../editors/integereditor.h"

IntegerDelegate::IntegerDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* IntegerDelegate::createEditor(QWidget *aParent, PropertyTreeWidgetItem * /*aItem*/) const
{
    IntegerEditor *editor=new IntegerEditor(aParent);

    return editor;
}
