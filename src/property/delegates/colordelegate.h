#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include "customdelegate.h"

class ColorDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit ColorDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // COLORDELEGATE_H
