#ifndef PROPERTYITEMDELEGATE_H
#define PROPERTYITEMDELEGATE_H

#include <QItemDelegate>

class PropertyItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit PropertyItemDelegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *aParent, const QStyleOptionViewItem &aOption, const QModelIndex &aIndex) const;
    void paint(QPainter *aPainter, const QStyleOptionViewItem &aOption, const QModelIndex &aIndex) const;
    void setEditorData(QWidget *aEditor, const QModelIndex &aIndex) const;
    void setModelData(QWidget *aEditor, QAbstractItemModel *aModel, const QModelIndex &aIndex) const;
    QSize sizeHint(const QStyleOptionViewItem &aOption, const QModelIndex &aIndex) const;
    void updateEditorGeometry(QWidget *aEditor, const QStyleOptionViewItem &aOption, const QModelIndex &aIndex) const;
};

#endif // PROPERTYITEMDELEGATE_H
