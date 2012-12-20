#ifndef STRINGLISTEDITOR_H
#define STRINGLISTEDITOR_H

#include "customeditor.h"

#include <QStringList>

namespace Ui {
class DialogEditor;
}

class StringListEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit StringListEditor(QWidget *parent = 0);
    ~StringListEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QStringList &aValue);
    void updateUI();
    void handleAttributes(const PropertyAttributes *aAttributes);

protected:
    void putFocus();
    void selectText();

private:
    Ui::DialogEditor *ui;
    QStringList mValue;
    const PropertyAttributes *mAttributes;
    QString mEchoMode;

private slots:
    void on_editButton_clicked();
};

#endif // STRINGLISTEDITOR_H
