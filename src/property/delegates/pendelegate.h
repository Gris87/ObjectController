#ifndef PENDELEGATE_H
#define PENDELEGATE_H

#include "customdelegate.h"

class PenDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit PenDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // PENDELEGATE_H
