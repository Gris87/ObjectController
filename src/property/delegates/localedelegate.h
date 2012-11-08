#ifndef LOCALEDELEGATE_H
#define LOCALEDELEGATE_H

#include "customdelegate.h"

class LocaleDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit LocaleDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // LOCALEDELEGATE_H
