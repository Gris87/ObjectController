#ifndef VECTOR4DEDITOR_H
#define VECTOR4DEDITOR_H

#include "customeditor.h"

#include <QVector4D>

namespace Ui {
class DialogEditor;
}

class Vector4DEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit Vector4DEditor(QWidget *parent = 0);
    ~Vector4DEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QVector4D &aValue);
    void updateUI();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QVector4D mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // VECTOR4DEDITOR_H
