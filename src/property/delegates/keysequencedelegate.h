#ifndef KEYSEQUENCEDELEGATE_H
#define KEYSEQUENCEDELEGATE_H

#include "customdelegate.h"

class KeySequenceDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit KeySequenceDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // KEYSEQUENCEDELEGATE_H
