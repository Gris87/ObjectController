#include "matrixdelegate.h"

#include "../editors/matrixeditor.h"
#include "../propertytreewidgetitem.h"

MatrixDelegate::MatrixDelegate(QObject *parent) :
    CustomDelegate(parent)
{
}

CustomEditor* MatrixDelegate::createEditor(QWidget *aParent) const
{
    return new MatrixEditor(aParent);
}

void MatrixDelegate::setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const
{
    MatrixEditor *aMatrixEditor=(MatrixEditor *)aEditor;

    switch (aItem->firstValue().type())
    {
        case QVariant::Matrix:
            aMatrixEditor->setValue(aItem->firstValue().value<QMatrix>());
        break;
        default:
            Q_ASSERT(false); // Impossible
        break;
    }
}
