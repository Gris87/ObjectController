#ifndef SIZEFDELEGATE_H
#define SIZEFDELEGATE_H

#include "customdelegate.h"

class SizeFDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit SizeFDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // SIZEFDELEGATE_H
