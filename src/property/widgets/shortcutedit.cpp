#include "shortcutedit.h"

#include <QKeyEvent>

ShortCutEdit::ShortCutEdit(QWidget *parent) :
    QLineEdit(parent)
{
    init(0);
}

ShortCutEdit::ShortCutEdit(const PropertyAttributes *aAttributes, QWidget *parent) :
    QLineEdit(parent)
{
    init(aAttributes);
}

void ShortCutEdit::init(const PropertyAttributes *aAttributes)
{
    if (aAttributes)
    {
        aAttributes->applyToWidget(this);
        mRejection=aAttributes->stringValues("rejectShortcuts");
    }
}

void ShortCutEdit::keyPressEvent(QKeyEvent *event)
{
    int aKey=event->key();

    if (
        aKey==Qt::Key_unknown
        ||
        aKey==Qt::Key_Control
        ||
        aKey==Qt::Key_Shift
        ||
        aKey==Qt::Key_Alt
        ||
        aKey==Qt::Key_Meta
       )
    {
        return;
    }

    Qt::KeyboardModifiers aModifiers=event->modifiers();

    if (aModifiers & Qt::ShiftModifier)
    {
        aKey|=Qt::SHIFT;
    }

    if (aModifiers & Qt::ControlModifier)
    {
        aKey|=Qt::CTRL;
    }

    if (aModifiers & Qt::AltModifier)
    {
        aKey|=Qt::ALT;
    }

    if (aModifiers & Qt::MetaModifier)
    {
        aKey|=Qt::META;
    }

    QString aShortcut=QKeySequence(aKey).toString();

    if (!mRejection.contains(aShortcut))
    {
        setText(aShortcut);
    }
}
