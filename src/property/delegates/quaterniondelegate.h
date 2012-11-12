#ifndef QUATERNIONDELEGATE_H
#define QUATERNIONDELEGATE_H

#include "customdelegate.h"

class QuaternionDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit QuaternionDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // QUATERNIONDELEGATE_H
