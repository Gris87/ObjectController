#ifndef EASINGCURVEEDITOR_H
#define EASINGCURVEEDITOR_H

#include "customeditor.h"

#include <QEasingCurve>

namespace Ui {
class DialogEditor;
}

class EasingCurveEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit EasingCurveEditor(QWidget *parent = 0);
    ~EasingCurveEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QEasingCurve &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QEasingCurve mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // EASINGCURVEEDITOR_H
