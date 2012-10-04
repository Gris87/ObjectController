#ifndef STRINGEDITOR_H
#define STRINGEDITOR_H

#include "customeditor.h"

namespace Ui {
class StringEditor;
}

class StringEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit StringEditor(QWidget *parent = 0);
    ~StringEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QString &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::StringEditor *ui;

private slots:
    void on_valueEdit_textEdited(const QString &aValue);
};

#endif // STRINGEDITOR_H
