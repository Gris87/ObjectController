#ifndef POINTFEDITOR_H
#define POINTFEDITOR_H

#include "customeditor.h"

#include <QPointF>

namespace Ui {
class DialogEditor;
}

class PointFEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit PointFEditor(QWidget *parent = 0);
    ~PointFEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPointF &aValue);
    void updateText();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QPointF mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // POINTFEDITOR_H
