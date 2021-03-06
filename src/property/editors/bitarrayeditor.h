#ifndef BITARRAYEDITOR_H
#define BITARRAYEDITOR_H

#include "customeditor.h"

#include <QBitArray>

namespace Ui {
class DialogEditor;
}

class BitArrayEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit BitArrayEditor(QWidget *parent = 0);
    ~BitArrayEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QBitArray &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QBitArray mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // BITARRAYEDITOR_H
