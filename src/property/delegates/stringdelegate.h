#ifndef STRINGDELEGATE_H
#define STRINGDELEGATE_H

#include "customdelegate.h"

class StringDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit StringDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // STRINGDELEGATE_H
