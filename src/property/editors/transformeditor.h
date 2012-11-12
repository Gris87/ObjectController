#ifndef TRANSFORMEDITOR_H
#define TRANSFORMEDITOR_H

#include "customeditor.h"

#include <QTransform>

namespace Ui {
class TransformEditor;
}

class TransformEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit TransformEditor(QWidget *parent = 0);
    ~TransformEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QTransform &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::TransformEditor *ui;
    QTransform mValue;

private slots:
    void on_editButton_clicked();
};

#endif // TRANSFORMEDITOR_H
