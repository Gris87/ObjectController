#ifndef MATRIXEDITOR_H
#define MATRIXEDITOR_H

#include "customeditor.h"

#include <QMatrix>

namespace Ui {
class DialogEditor;
}

class MatrixEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit MatrixEditor(QWidget *parent = 0);
    ~MatrixEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QMatrix &aValue);
    void updateText();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QMatrix mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // MATRIXEDITOR_H
