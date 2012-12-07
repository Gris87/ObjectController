#ifndef INTEGEREDITOR_H
#define INTEGEREDITOR_H

#include "customeditor.h"

namespace Ui {
class IntegerEditor;
}

class IntegerEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit IntegerEditor(QWidget *parent = 0);
    ~IntegerEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const qint8 &aValue);
    void setValue(const quint8 &aValue);
    void setValue(const qint16 &aValue);
    void setValue(const quint16 &aValue);
    void setValue(const qint32 &aValue);
    void setValue(const quint32 &aValue);
    void setValue(const qint64 &aValue);
    void setValue(const quint64 &aValue);
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::IntegerEditor *ui;

private slots:
    void on_valueSpinBox_valueChanged(int aValue);
};

#endif // INTEGEREDITOR_H
