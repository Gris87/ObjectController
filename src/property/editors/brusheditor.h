#ifndef BRUSHEDITOR_H
#define BRUSHEDITOR_H

#include "customeditor.h"

#include <QBrush>

namespace Ui {
class BrushEditor;
}

class BrushEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit BrushEditor(QWidget *parent = 0);
    ~BrushEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QBrush &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::BrushEditor *ui;
    QBrush mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // BRUSHEDITOR_H
