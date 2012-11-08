#ifndef RECTDELEGATE_H
#define RECTDELEGATE_H

#include "customdelegate.h"

class RectDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit RectDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // RECTDELEGATE_H
