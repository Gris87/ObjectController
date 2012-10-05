#ifndef BYTEARRAYEDITOR_H
#define BYTEARRAYEDITOR_H

#include "customeditor.h"

namespace Ui {
class ByteArrayEditor;
}

class ByteArrayEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit ByteArrayEditor(QWidget *parent = 0);
    ~ByteArrayEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QByteArray &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::ByteArrayEditor *ui;
};

#endif // BYTEARRAYEDITOR_H
