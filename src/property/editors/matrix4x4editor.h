#ifndef MATRIX4X4EDITOR_H
#define MATRIX4X4EDITOR_H

#include "customeditor.h"

#include <QMatrix4x4>

namespace Ui {
class Matrix4x4Editor;
}

class Matrix4x4Editor : public CustomEditor
{
    Q_OBJECT

public:
    explicit Matrix4x4Editor(QWidget *parent = 0);
    ~Matrix4x4Editor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QMatrix4x4 &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::Matrix4x4Editor *ui;
    QMatrix4x4 mValue;

private slots:
    void on_editButton_clicked();
};

#endif // MATRIX4X4EDITOR_H
