#ifndef INTEGERDELEGATE_H
#define INTEGERDELEGATE_H

#include "customdelegate.h"

class IntegerDelegate : public CustomDelegate
{
    Q_OBJECT
public:
    explicit IntegerDelegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *aParent, const QStyleOptionViewItem &aOption, const QModelIndex &aIndex) const;
};

#endif // INTEGERDELEGATE_H
