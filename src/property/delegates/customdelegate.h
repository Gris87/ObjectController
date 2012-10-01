#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QItemDelegate>

#include "../editors/customeditor.h"

class PropertyTreeWidgetItem;

class CustomDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CustomDelegate(QObject *parent = 0);

    virtual CustomEditor* createEditor(QWidget *aParent, PropertyTreeWidgetItem *aItem) const;
};

#endif // CUSTOMDELEGATE_H
