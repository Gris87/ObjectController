#ifndef MATRIX4X4DELEGATE_H
#define MATRIX4X4DELEGATE_H

#include "customdelegate.h"

class Matrix4x4Delegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit Matrix4x4Delegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // MATRIX4X4DELEGATE_H
