#ifndef PALETTEDELEGATE_H
#define PALETTEDELEGATE_H

#include "customdelegate.h"

class PaletteDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit PaletteDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // PALETTEDELEGATE_H
