#ifndef PROPERTYTREEWIDGET_H
#define PROPERTYTREEWIDGET_H

#include <QTreeWidget>

#include "propertygroup.h"
#include "propertyitemdelegate.h"

class PropertyTreeWidget : public QTreeWidget
{
    Q_OBJECT

    friend class PropertyItemDelegate;

public:
    explicit PropertyTreeWidget(QWidget *parent = 0);

    void fillByPropertyGroups(QList<PropertyGroup *> aGroups);
    void update(const QObjectList &aObjects);

protected:
    PropertyItemDelegate *mItemDelegate;

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // PROPERTYTREEWIDGET_H
