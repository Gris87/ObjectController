#ifndef QUATERNIONEDITOR_H
#define QUATERNIONEDITOR_H

#include "customeditor.h"

#include <QQuaternion>

namespace Ui {
class DialogEditor;
}

class QuaternionEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit QuaternionEditor(QWidget *parent = 0);
    ~QuaternionEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QQuaternion &aValue);
    void updateUI();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QQuaternion mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // QUATERNIONEDITOR_H
