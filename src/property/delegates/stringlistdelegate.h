#ifndef STRINGLISTDELEGATE_H
#define STRINGLISTDELEGATE_H

#include "customdelegate.h"

class StringListDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit StringListDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // STRINGLISTDELEGATE_H
