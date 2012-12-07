#include "customeditor.h"

CustomEditor::CustomEditor(QWidget *parent) :
    QWidget(parent)
{
    mCanEmitValueChangedSignal=false;
    mDelay=100;

    setAutoFillBackground(true);

    connect(&mModificationTimer, SIGNAL(timeout()), this, SLOT(modificationSlot()));
    QTimer::singleShot(0, this, SLOT(afterCreatingSlot()));
}

CustomEditor::~CustomEditor()
{
    if (mModificationTimer.isActive())
    {
        modificationSlot();
    }
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

void CustomEditor::modificationDone(const QVariant &aNewValue)
{
    if (mCanEmitValueChangedSignal)
    {
        mNewValue=aNewValue;

        mModificationTimer.stop();
        mModificationTimer.start(mDelay);
    }
}

void CustomEditor::modificationSlot()
{
    mModificationTimer.stop();
    emit valueChanged(mNewValue);
}

void CustomEditor::afterCreatingSlot()
{
    mCanEmitValueChangedSignal=true;

    putFocus();
    selectText();
}

void CustomEditor::setIcon(const QIcon &/*aIcon*/)
{
    // Nothing
}

void CustomEditor::handleAttributes(const PropertyAttributes *aAttributes)
{
    mDelay=aAttributes->intValue("delay", mDelay);

    if (mDelay<0)
    {
        mDelay=0;
    }
}
