#ifndef KEYSEQUENCEEDITOR_H
#define KEYSEQUENCEEDITOR_H

#include "customeditor.h"

#include <QKeySequence>

namespace Ui {
class KeySequenceEditor;
}

class KeySequenceEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit KeySequenceEditor(QWidget *parent = 0);
    ~KeySequenceEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QKeySequence &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::KeySequenceEditor *ui;
    QKeySequence mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // KEYSEQUENCEEDITOR_H
