#ifndef MATRIXEDITOR_H
#define MATRIXEDITOR_H

#include "customeditor.h"

#include <QMatrix>

namespace Ui {
class MatrixEditor;
}

class MatrixEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit MatrixEditor(QWidget *parent = 0);
    ~MatrixEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QMatrix &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::MatrixEditor *ui;
    QMatrix mValue;

private slots:
    void on_editButton_clicked();
};

#endif // MATRIXEDITOR_H
