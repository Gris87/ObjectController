#ifndef POINTFDELEGATE_H
#define POINTFDELEGATE_H

#include "customdelegate.h"

class PointFDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit PointFDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // POINTFDELEGATE_H
