#ifndef KEYSEQUENCEEDITDIALOG_H
#define KEYSEQUENCEEDITDIALOG_H

#include <QDialog>

#include <QKeySequence>

#include "../widgets/shortcutedit.h"
#include "../propertyattributes.h"

namespace Ui {
class KeySequenceEditDialog;
}

class KeySequenceEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeySequenceEditDialog(QWidget *parent = 0);
    explicit KeySequenceEditDialog(QKeySequence aKeySequence, QWidget *parent = 0);
    explicit KeySequenceEditDialog(const PropertyAttributes *aAttributes, QWidget *parent = 0);
    explicit KeySequenceEditDialog(QKeySequence aKeySequence, const PropertyAttributes *aAttributes, QWidget *parent = 0);
    ~KeySequenceEditDialog();

    QKeySequence resultValue() const;

private:
    Ui::KeySequenceEditDialog *ui;
    ShortCutEdit              *mShortCutEdit;

    void init(QKeySequence aKeySequence, const PropertyAttributes *aAttributes);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // KEYSEQUENCEEDITDIALOG_H
