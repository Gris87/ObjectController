#ifndef BYTEARRAYDELEGATE_H
#define BYTEARRAYDELEGATE_H

#include "customdelegate.h"

class ByteArrayDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit ByteArrayDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // BYTEARRAYDELEGATE_H
