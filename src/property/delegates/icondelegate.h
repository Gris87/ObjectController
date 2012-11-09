#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H

#include "customdelegate.h"

class IconDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit IconDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // ICONDELEGATE_H
