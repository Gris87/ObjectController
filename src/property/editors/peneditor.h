#ifndef PENEDITOR_H
#define PENEDITOR_H

#include "customeditor.h"

#include <QPen>

namespace Ui {
class DialogEditor;
}

class PenEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit PenEditor(QWidget *parent = 0);
    ~PenEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPen &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QPen mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // PENEDITOR_H
