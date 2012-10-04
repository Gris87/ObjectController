#ifndef BOOLEDITOR_H
#define BOOLEDITOR_H

#include "customeditor.h"

namespace Ui {
class BoolEditor;
}

class BoolEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit BoolEditor(QWidget *parent = 0);
    ~BoolEditor();

    void setValue(const bool &aValue);

protected:
    void putFocus();

private:
    Ui::BoolEditor *ui;

private slots:
    void on_valueCheckBox_toggled(bool checked);
};

#endif // BOOLEDITOR_H
