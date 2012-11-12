#ifndef ICONEDITDIALOG_H
#define ICONEDITDIALOG_H

#include <QDialog>

#include <QIcon>
#include <QCheckBox>

#include "../widgets/paintframe.h"

namespace Ui {
class IconEditDialog;
}

class IconEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IconEditDialog(QIcon aIcon, QWidget *parent = 0);
    ~IconEditDialog();

    QIcon resultValue() const;

private:
    struct PageEntry
    {
        QCheckBox    *checkbox;
        PaintFrame   *paintframe;
        QIcon::Mode   mode;
        QIcon::State  state;
    };

    Ui::IconEditDialog *ui;
    QList<PageEntry>    mPages;

    QString modeToString(const QIcon::Mode &aMode) const;
    QString stateToString(const QIcon::State &aState) const;

private slots:
    void useCheckBoxToggled(bool aChecked);

    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // ICONEDITDIALOG_H
