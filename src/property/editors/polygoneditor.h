#ifndef POLYGONEDITOR_H
#define POLYGONEDITOR_H

#include "customeditor.h"

#include <QPolygon>

namespace Ui {
class PolygonEditor;
}

class PolygonEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit PolygonEditor(QWidget *parent = 0);
    ~PolygonEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QPolygon &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::PolygonEditor *ui;
    QPolygon mValue;
    const PropertyAttributes *mAttributes;

private slots:
    void on_editButton_clicked();
};

#endif // POLYGONEDITOR_H
