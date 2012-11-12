#ifndef VECTOR2DDELEGATE_H
#define VECTOR2DDELEGATE_H

#include "customdelegate.h"

class Vector2DDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit Vector2DDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // VECTOR2DDELEGATE_H
