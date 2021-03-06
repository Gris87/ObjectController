#ifndef BRUSHEDITOR_H
#define BRUSHEDITOR_H

#include "customeditor.h"

#include <QBrush>

namespace Ui {
class DialogEditor;
}

class BrushEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit BrushEditor(QWidget *parent = 0);
    ~BrushEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QBrush &aValue);
    void updateText();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QBrush mValue;
    const PropertyAttributes *mAttributes;
    bool mAlphaEnabled;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // BRUSHEDITOR_H
