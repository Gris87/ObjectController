#ifndef CHARDELEGATE_H
#define CHARDELEGATE_H

#include "customdelegate.h"

class CharDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit CharDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // CHARDELEGATE_H
