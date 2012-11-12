#ifndef VECTOR4DDELEGATE_H
#define VECTOR4DDELEGATE_H

#include "customdelegate.h"

class Vector4DDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit Vector4DDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // VECTOR4DDELEGATE_H
