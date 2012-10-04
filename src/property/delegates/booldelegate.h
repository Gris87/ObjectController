#ifndef BOOLDELEGATE_H
#define BOOLDELEGATE_H

#include "customdelegate.h"

class BoolDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit BoolDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // BOOLDELEGATE_H
