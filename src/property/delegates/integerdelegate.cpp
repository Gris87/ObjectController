#include "integerdelegate.h"

#include "../editors/integereditor.h"

IntegerDelegate::IntegerDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

QWidget* IntegerDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &/*aOption*/, const QModelIndex &aIndex) const
{
    IntegerEditor *editor=new IntegerEditor(aParent);

    return editor;
}
