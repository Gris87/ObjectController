#ifndef COLOREDITOR_H
#define COLOREDITOR_H

#include "customeditor.h"

#include <QColor>

namespace Ui {
class DialogEditor;
}

class ColorEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit ColorEditor(QWidget *parent = 0);
    ~ColorEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QColor &aValue);
    void updateText();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QColor mValue;
    const PropertyAttributes *mAttributes;
    bool mAlphaEnabled;

private slots:
    void on_editButton_clicked();
};

#endif // COLOREDITOR_H
