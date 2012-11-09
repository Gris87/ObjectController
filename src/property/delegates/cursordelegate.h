#ifndef CURSORDELEGATE_H
#define CURSORDELEGATE_H

#include "customdelegate.h"

class CursorDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit CursorDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // CURSORDELEGATE_H
