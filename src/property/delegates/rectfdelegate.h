#ifndef RECTFDELEGATE_H
#define RECTFDELEGATE_H

#include "customdelegate.h"

class RectFDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit RectFDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // RECTFDELEGATE_H
