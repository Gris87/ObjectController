#ifndef REGIONEDITOR_H
#define REGIONEDITOR_H

#include "customeditor.h"

#include <QRegion>

namespace Ui {
class DialogEditor;
}

class RegionEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit RegionEditor(QWidget *parent = 0);
    ~RegionEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QRegion &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QRegion mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // REGIONEDITOR_H
