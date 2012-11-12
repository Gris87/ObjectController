#ifndef TEXTFORMATDELEGATE_H
#define TEXTFORMATDELEGATE_H

#include "customdelegate.h"

class TextFormatDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit TextFormatDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // TEXTFORMATDELEGATE_H
