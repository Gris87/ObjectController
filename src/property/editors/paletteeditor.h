#ifndef PALETTEEDITOR_H
#define PALETTEEDITOR_H

#include "customeditor.h"

#include <QPalette>

namespace Ui {
class PaletteEditor;
}

class PaletteEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit PaletteEditor(QWidget *parent = 0);
    ~PaletteEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPalette &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::PaletteEditor *ui;
    QPalette mValue;

private slots:
    void on_editButton_clicked();
};

#endif // PALETTEEDITOR_H
