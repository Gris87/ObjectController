#ifndef FONTDELEGATE_H
#define FONTDELEGATE_H

#include "customdelegate.h"

class FontDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit FontDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // FONTDELEGATE_H
