#ifndef POINTDELEGATE_H
#define POINTDELEGATE_H

#include "customdelegate.h"

class PointDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit PointDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // POINTDELEGATE_H
