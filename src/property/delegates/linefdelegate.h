#ifndef LINEFDELEGATE_H
#define LINEFDELEGATE_H

#include "customdelegate.h"

class LineFDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit LineFDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // LINEFDELEGATE_H
