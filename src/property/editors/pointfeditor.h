#ifndef POINTFEDITOR_H
#define POINTFEDITOR_H

#include "customeditor.h"

#include <QPointF>

namespace Ui {
class PointFEditor;
}

class PointFEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit PointFEditor(QWidget *parent = 0);
    ~PointFEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPointF &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::PointFEditor *ui;
    QPointF mValue;

private slots:
    void on_editButton_clicked();
};

#endif // POINTFEDITOR_H
