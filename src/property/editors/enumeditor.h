#ifndef ENUMEDITOR_H
#define ENUMEDITOR_H

#include "customeditor.h"

#include <QMetaEnum>

namespace Ui {
class EnumEditor;
}

class EnumEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit EnumEditor(QWidget *parent = 0);
    ~EnumEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(QMetaEnum *aMetaEnum, const int &aValue);

protected:
    void putFocus();

private:
    Ui::EnumEditor *ui;
    QMetaEnum      *mMetaEnum;

private slots:
    void on_valueComboBox_currentIndexChanged(const QString &aValue);
};

#endif // ENUMEDITOR_H
