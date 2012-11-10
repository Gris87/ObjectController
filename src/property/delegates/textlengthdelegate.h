#ifndef TEXTLENGTHDELEGATE_H
#define TEXTLENGTHDELEGATE_H

#include "customdelegate.h"

class TextLengthDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit TextLengthDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // TEXTLENGTHDELEGATE_H
