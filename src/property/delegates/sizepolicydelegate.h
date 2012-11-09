#ifndef SIZEPOLICYDELEGATE_H
#define SIZEPOLICYDELEGATE_H

#include "customdelegate.h"

class SizePolicyDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit SizePolicyDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // SIZEPOLICYDELEGATE_H
