#ifndef VECTOR3DEDITOR_H
#define VECTOR3DEDITOR_H

#include "customeditor.h"

#include <QVector3D>

namespace Ui {
class Vector3DEditor;
}

class Vector3DEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit Vector3DEditor(QWidget *parent = 0);
    ~Vector3DEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QVector3D &aValue);

protected:
    void putFocus();
    void selectText();

private:
    Ui::Vector3DEditor *ui;
    QVector3D mValue;

private slots:
    void on_editButton_clicked();
};

#endif // VECTOR3DEDITOR_H
