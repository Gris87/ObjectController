#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include "customdelegate.h"

class DateDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit DateDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // DATEDELEGATE_H
