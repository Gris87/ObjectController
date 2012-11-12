#ifndef VECTOR3DDELEGATE_H
#define VECTOR3DDELEGATE_H

#include "customdelegate.h"

class Vector3DDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit Vector3DDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // VECTOR3DDELEGATE_H
