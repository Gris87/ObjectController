#ifndef SIZEDELEGATE_H
#define SIZEDELEGATE_H

#include "customdelegate.h"

class SizeDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit SizeDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // SIZEDELEGATE_H
