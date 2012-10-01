#ifndef DEFAULTEDITOR_H
#define DEFAULTEDITOR_H

#include "customeditor.h"

namespace Ui {
class DefaultEditor;
}

class DefaultEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit DefaultEditor(QWidget *parent = 0);
    ~DefaultEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QString &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DefaultEditor *ui;
};

#endif // DEFAULTEDITOR_H
