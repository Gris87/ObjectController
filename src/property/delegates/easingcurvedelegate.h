#ifndef EASINGCURVEDELEGATE_H
#define EASINGCURVEDELEGATE_H

#include "customdelegate.h"

class EasingCurveDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit EasingCurveDelegate(QObject *parent = 0);

    CustomEditor* createEditor(QWidget *aParent) const;
    void setEditorData(QWidget *aEditor, PropertyTreeWidgetItem *aItem) const;
};

#endif // EASINGCURVEDELEGATE_H
