#ifndef LINEDELEGATE_H
#define LINEDELEGATE_H

#include "customdelegate.h"

class LineDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit LineDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // LINEDELEGATE_H
