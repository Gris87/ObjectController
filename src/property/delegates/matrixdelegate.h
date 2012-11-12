#ifndef MATRIXDELEGATE_H
#define MATRIXDELEGATE_H

#include "customdelegate.h"

class MatrixDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit MatrixDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // MATRIXDELEGATE_H
