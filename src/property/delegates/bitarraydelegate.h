#ifndef BITARRAYDELEGATE_H
#define BITARRAYDELEGATE_H

#include "customdelegate.h"

class BitArrayDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit BitArrayDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // BITARRAYDELEGATE_H
