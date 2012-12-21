#ifndef PALETTEEDITOR_H
#define PALETTEEDITOR_H

#include "customeditor.h"

#include <QPalette>

namespace Ui {
class DialogEditor;
}

class PaletteEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit PaletteEditor(QWidget *parent = 0);
    ~PaletteEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPalette &aValue);
    void updateText();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QPalette mValue;
    const PropertyAttributes *mAttributes;
    bool mAlphaEnabled;

private slots:
    void on_editButton_clicked();
};

#endif // PALETTEEDITOR_H
