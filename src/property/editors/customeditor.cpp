#include "customeditor.h"

#include <QTimer>

CustomEditor::CustomEditor(QWidget *parent) :
    QWidget(parent)
{
    mCanEmitValueChangedSignal=false;

    setAutoFillBackground(true);

    QTimer::singleShot(0, this, SLOT(afterCreatingSlot()));
}

void CustomEditor::keyPressEvent(QKeyEvent * /*event*/)
{
    // Nothing
}

void CustomEditor::mousePressEvent(QMouseEvent * /*event*/)
{
    putFocus();
}

void CustomEditor::putFocus()
{
    // Nothing
}

void CustomEditor::selectText()
{
    // Nothing
}

void CustomEditor::afterCreatingSlot()
{
    mCanEmitValueChangedSignal=true;

    putFocus();
    selectText();
}

void CustomEditor::setIcon(const QIcon &aIcon)
{
    // Nothing
}
