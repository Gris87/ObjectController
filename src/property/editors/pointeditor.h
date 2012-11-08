#ifndef POINTEDITOR_H
#define POINTEDITOR_H

#include "customeditor.h"

#include <QPoint>

namespace Ui {
class PointEditor;
}

class PointEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit PointEditor(QWidget *parent = 0);
    ~PointEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPoint &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::PointEditor *ui;
    QPoint mValue;

private slots:
    void on_editButton_clicked();
};

#endif // POINTEDITOR_H