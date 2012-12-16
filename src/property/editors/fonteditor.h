#ifndef FONTEDITOR_H
#define FONTEDITOR_H

#include "customeditor.h"

#include <QFont>

namespace Ui {
class FontEditor;
}

class FontEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit FontEditor(QWidget *parent = 0);
    ~FontEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QFont &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::FontEditor *ui;
    QFont mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // FONTEDITOR_H
