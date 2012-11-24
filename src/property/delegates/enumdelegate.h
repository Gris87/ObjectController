#ifndef ENUMDELEGATE_H
#define ENUMDELEGATE_H

#include "customdelegate.h"

class EnumDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit EnumDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // ENUMDELEGATE_H
