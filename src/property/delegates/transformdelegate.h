#ifndef TRANSFORMDELEGATE_H
#define TRANSFORMDELEGATE_H

#include "customdelegate.h"

class TransformDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit TransformDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // TRANSFORMDELEGATE_H
