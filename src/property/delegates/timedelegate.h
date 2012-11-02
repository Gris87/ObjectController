#ifndef TIMEDELEGATE_H
#define TIMEDELEGATE_H

#include "customdelegate.h"

class TimeDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit TimeDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // TIMEDELEGATE_H
