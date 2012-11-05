#ifndef PIXMAPDELEGATE_H
#define PIXMAPDELEGATE_H

#include "customdelegate.h"

class PixmapDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit PixmapDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // PIXMAPDELEGATE_H
