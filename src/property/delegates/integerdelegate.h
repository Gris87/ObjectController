#ifndef INTEGERDELEGATE_H
#define INTEGERDELEGATE_H

#include "customdelegate.h"

class IntegerDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit IntegerDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // INTEGERDELEGATE_H
