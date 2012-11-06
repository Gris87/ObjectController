#ifndef BRUSHDELEGATE_H
#define BRUSHDELEGATE_H

#include "customdelegate.h"

class BrushDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit BrushDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // BRUSHDELEGATE_H
