#ifndef TRANSFORMEDITOR_H
#define TRANSFORMEDITOR_H

#include "customeditor.h"

#include <QTransform>

namespace Ui {
class DialogEditor;
}

class TransformEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit TransformEditor(QWidget *parent = 0);
    ~TransformEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QTransform &aValue);
    void updateText();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QTransform mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // TRANSFORMEDITOR_H
