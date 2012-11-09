#ifndef POLYGONDELEGATE_H
#define POLYGONDELEGATE_H

#include "customdelegate.h"

class PolygonDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit PolygonDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // POLYGONDELEGATE_H
