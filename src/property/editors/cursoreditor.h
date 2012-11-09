#ifndef CURSOREDITOR_H
#define CURSOREDITOR_H

#include "customeditor.h"

namespace Ui {
class CursorEditor;
}

class CursorEditor : public CustomEditor
{
    Q_OBJECT

public:
    explicit CursorEditor(QWidget *parent = 0);
    ~CursorEditor();

    void setIcon(const QIcon &aIcon);
    void setValue(const QCursor &aValue);

protected:
    void putFocus();

private:
    Ui::CursorEditor *ui;
    QCursor           mCursor;
    QCursor           mBitmapCursor;
    QTimer            mHotSpotTimer;

private slots:
    void hotSpotChanged();

    void on_valueComboBox_currentIndexChanged(const QString &aValue);
    void on_xSpinBox_valueChanged(int aValue);
    void on_ySpinBox_valueChanged(int aValue);
    void on_bitmapButton_clicked();
    void on_maskButton_clicked();
    void on_pixmapButton_clicked();
};

#endif // CURSOREDITOR_H
