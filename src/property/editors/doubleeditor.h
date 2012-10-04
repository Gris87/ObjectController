#ifndef DOUBLEEDITOR_H
#define DOUBLEEDITOR_H

#include "customeditor.h"

namespace Ui {
class DoubleEditor;
}

class DoubleEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit DoubleEditor(QWidget *parent = 0);
    ~DoubleEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const double &aValue);
    void setValue(const float &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DoubleEditor *ui;

private slots:
    void on_valueSpinBox_valueChanged(double aValue);
};

#endif // DOUBLEEDITOR_H
