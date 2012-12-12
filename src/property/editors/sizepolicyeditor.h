#ifndef SIZEPOLICYEDITOR_H
#define SIZEPOLICYEDITOR_H

#include "customeditor.h"

#include <QSizePolicy>

namespace Ui {
class SizePolicyEditor;
}

class SizePolicyEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit SizePolicyEditor(QWidget *parent = 0);
    ~SizePolicyEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QSizePolicy &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::SizePolicyEditor *ui;
    QSizePolicy mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // SIZEPOLICYEDITOR_H
