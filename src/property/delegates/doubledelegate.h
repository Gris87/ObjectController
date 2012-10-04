#ifndef DOUBLEDELEGATE_H
#define DOUBLEDELEGATE_H

#include "customdelegate.h"

class DoubleDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit DoubleDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // DOUBLEDELEGATE_H
