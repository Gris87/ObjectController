#ifndef VECTOR2DEDITOR_H
#define VECTOR2DEDITOR_H

#include "customeditor.h"

#include <QVector2D>

namespace Ui {
class Vector2DEditor;
}

class Vector2DEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit Vector2DEditor(QWidget *parent = 0);
    ~Vector2DEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QVector2D &aValue);
    void updateUI();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::Vector2DEditor *ui;
    QVector2D mValue;
    const PropertyAttributes *mAttributes;
    int mDecimals;

private slots:
    void on_editButton_clicked();
};

#endif // VECTOR2DEDITOR_H
