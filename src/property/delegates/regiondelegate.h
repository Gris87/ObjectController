#ifndef REGIONDELEGATE_H
#define REGIONDELEGATE_H

#include "customdelegate.h"

class RegionDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit RegionDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // REGIONDELEGATE_H
