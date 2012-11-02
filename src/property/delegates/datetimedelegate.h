#ifndef DATETIMEDELEGATE_H
#define DATETIMEDELEGATE_H

#include "customdelegate.h"

class DateTimeDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit DateTimeDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // DATETIMEDELEGATE_H
